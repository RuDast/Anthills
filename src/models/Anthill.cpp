#include "Anthill.h"
#include <iostream>
#include "Food.h"
#include "../constants.h"
#include "../views/AntRender.h"
#include "../views/FoodRender.h"
#include "informers/NotificationListener.h"
#include "Roles/CleanerRole.h"
#include "Roles/CollectorRole.h"
#include "Roles/NoneRole.h"
#include <math.h>

#include "../views/enemy_render.h"
#include "Roles/SoliderRole.h"

Anthill::Anthill(RenderManager &render_manager,
                 sf::Text &food_count_text,
                 NotificationListener *notification_manager) : render_manager_(render_manager),
                                                               food_count(food_count_text),
                                                               notification_manager(notification_manager) {
    size = Config::Anthill::default_size;
    for (int i = 0; i < Config::Anthill::spawners_count; i++) {
        ants_in_spawners[i] = nullptr;
    }
    for (int i = 0; i < Config::Anthill::spawners_count; ++i) {
        free_spawners[i] = true;
    }

}

bool Anthill::add_ant(Ant *ant) {
    if (size >= Config::Anthill::max_size) {
        return false;
    }

    list_of_ants.push_back(ant);
    return true;
}

void Anthill::update(const float deltaTime) {
    last_age_update_time += deltaTime;

    if (last_age_update_time >= Config::Ant::age_update_time_interval) {
        last_age_update_time = 0;

        for (const auto ant: list_of_ants) {
            if (food_quantity - 1 >= 0) {
                food_quantity--;
                update_food_count_text();
            } else
                ant->lower_health(Config::Anthill::hunger_damage);
        }
    }

    for (unsigned i = 0; i < list_of_ants.size();) {
        list_of_ants[i]->update(deltaTime);
        if (!list_of_ants[i]->get_trash()) {
            delete list_of_ants[i];
            list_of_ants.erase(list_of_ants.begin() + i);
        } else ++i;
    }

    clear_collected_corpses();

    spawn_ant(deltaTime);
    spawn_food(deltaTime);

    go_to_food(); // сбор еды
    clear_delivered_food(); // удалили уже доставленные крошки (не трогает Corpses)

    go_to_corpse(); // здесь распределяем чистильщиков по трупам
    // clear_collected_corpses();; // очистка собранных трупов
    spawn_enemy(deltaTime);
    CheckCollisions(list_of_enemy, list_of_ants);
    for(int i = 0; i < list_of_enemy.size();)
    {
        if (list_of_enemy[i] == nullptr) {
            i++;
            continue;
        }
        list_of_enemy[i]->update(deltaTime);
        if(!list_of_enemy[i]->getIsAlive())
        {
            delete list_of_enemy[i];
            list_of_enemy.erase(list_of_enemy.begin() + i);
        } else ++i;
    }
}

void Anthill::print() const {
    for (const auto &ant: list_of_ants) {
        ant->print();
    }
}

void Anthill::spawn_ant(const float deltaTime) {
    last_spawn_time += deltaTime;

    if (last_spawn_time < Config::Anthill::spawn_interval) {
        return;
    }

    last_spawn_time = 0;
    for (unsigned i = 0; i < Config::Anthill::spawners_count; ++i) {
        if (!free_spawners[i] && ants_in_spawners[i]->getRole() != None) {
            free_spawners[i] = true;
        }

        if (food_quantity > 0 && free_spawners[i] && food_quantity >= list_of_ants.size() * 2) {
            const auto new_ant = new Ant(spawner_x[i], spawner_y);
            free_spawners[i] = false;
            food_quantity--;
            update_food_count_text();
            ants_in_spawners[i] = new_ant;
            add_ant(new_ant);

            AntRender *new_ant_render = new AntRender(*new_ant);
            new_ant->add_subscriber(new_ant_render);
            render_manager_.addDrawable(new_ant_render);
            new_ant->set_anthill(this);

            new_ant->add_new_subscriber(notification_manager);
        }
    }
}

void Anthill::update_food_count_text() const {
    food_count.setString("Food: " + std::to_string(food_quantity));
}



void Anthill::CheckCollisions(const std::vector<Enemy*>& enemies, const std::vector<Ant*>& ants)
{

    for (Enemy* enemy : enemies) {
        if (!enemy->getIsAlive()) continue;
        bool enemyWasKilled = false;

        for (Ant* ant : ants) {
            if (!ant->isAlive()) continue;

            float dX = enemy->getX() - ant->getX();
            float dY = enemy->getY() - ant->getY();
            float distanceSquared = dX * dX + dY * dY;

            if (distanceSquared <= Config::Enemy::distance*Config::Enemy::distance) {
                if (ant->getRole() == Soldier) {
                    enemy->setAlive(false);
                    enemyWasKilled = true;
                    current_count_enemy--;
                }
                else {
                    ant->kill();
                }
                break;
            }
        }

        if (enemyWasKilled)  { continue;
        }
    }



}

void Anthill::spawn_food(float deltaTime )
{
    last_food_spawn_time += deltaTime;

    if (last_food_spawn_time < Config::Food::spawn_interval) {
        return;
    }

    last_food_spawn_time = 0;

    if (current_count_food < Config::Food::max_count_of_food) {
        const auto new_food = new Food();
        DrawableEntity *new_food_render = new FoodRender(*new_food);
        render_manager_.addDrawable(new_food_render);


        current_count_food++;
        foods.push_back(new_food);
    }
}

void Anthill::go_to_food() {
    for (const auto food_: foods) {
        if (food_->getState() != FoodState::free)
            continue;
        for (auto &ant: list_of_ants) {
            if (ant->get_state() == State::free && ant->getRole() == Collector) {
                ant->set_state(State::busy);
                food_->setState(FoodState::wait);
                ant->setTarget(food_->getX(), food_->getY());
                ant->set_food(food_);
                return;
            }
        }
    }
}

void Anthill::clear_delivered_food() {
    for (size_t i = 0; i < foods.size();) {
        if (foods[i]->getState() == FoodState::on_sklad) {
            delete foods[i];
            foods.erase(foods.begin() + i);
            current_count_food--;
        } else {
            ++i;
        }
    }
}

void Anthill::spawn_enemy(float deltaTime)
{
    last_enemy_spawn_time += deltaTime;
void Anthill::addDeliveredFood() {
    food_quantity++;
    update_food_count_text();
}

    if (last_enemy_spawn_time < Config::Enemy::spawn_interval) {
        return;
    }

    last_enemy_spawn_time = 0;

        if (current_count_enemy < Config::Enemy::max_count_of_enemy)
        {
            Enemy* new_enemy = new Enemy(50 + rand()%300,200);
            EnemyRender *new_enemy_render = new EnemyRender(*new_enemy);
            render_manager_.addDrawable(new_enemy_render);

            list_of_enemy.push_back(new_enemy);
            current_count_enemy++;
        }

}

void Anthill::go_to_corpse() {
    // std::cout << "[INFO] go_to_corpse called. Corpses: " << corpses.size()
    //           << ", ants: " << list_of_ants.size() << "\n";
    //
    // // 1) Выведем все состояния трупов
    // for (auto c : corpses) {
    //     std::cout << "  CORPSE " << c
    //               << " state=" << int(c->getState())
    //               << "\n";
    // }

    // 2) Выведем всех уборщиков и их состояния
    // for (auto &ant : list_of_ants) {
    //     std::cout << "  ANT     " << ant
    //               << " state="     << int(ant->get_state())
    //               << " isCleaner=" << ant->getRole()->isCleaner()
    //               << "\n";
    // }

    // 3) Пытаемся назначить первого свободного уборщика на первый свободный труп
    for (auto c : corpses) {
        if (c->getState() != CorpseState::free) {
            // std::cout << "    skip corpse " << c << " (not free)\n";
            continue;
        }
        for (auto &ant : list_of_ants) {
            if (ant->get_state() == State::free && ant->getRole()->isCleaner()) {
            //     std::cout << "[ASSIGN] ANT " << ant
            //               << " -> CORPSE " << c << "\n";
                ant->set_state(State::busy);
                c->setState(CorpseState::wait);
                ant->setTarget(c->getX(), c->getY());
                ant->setCorpse(c);
                return;
            } else {
            //     std::cout << "    ant " << ant
            //               << (ant->get_state() != State::free ? " not free"
            //                  : ant->getRole()->isCleaner() ? ""
            //                  : " not cleaner")
            //               << "\n";
            }
        }
        // если мы сюда дошли — значит ни один антик не подошёл
        std::cout << "  no free cleaner for corpse " << c << "\n";
    }
}


void Anthill::clear_collected_corpses() {
    for (size_t i = 0; i < corpses.size();) {
        if (corpses[i]->getState() == CorpseState::on_trash) {
            delete corpses[i];
            corpses.erase(corpses.begin() + i);
        } else {
            ++i;
        }
    }
}

void Anthill::addCorpse(Corpse *c) {
    corpses.push_back(c);
    std::cout << "Добавили труп" << std::endl;
    // создаём рендер и добавляем в менеджер
    auto *r = new CorpseRender(*c);
    render_manager_.addDrawable(r);
}
