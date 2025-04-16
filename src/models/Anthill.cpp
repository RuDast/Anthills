#include "Anthill.h"

#include "Food.h"
#include "../constants.h"
#include "../views/AntRender.h"
#include "../views/FoodRender.h"
#include "Roles/CollectorRole.h"
#include "Roles/NoneRole.h"

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
        if (!list_of_ants[i]->isAlive()) {
            delete list_of_ants[i];
            list_of_ants.erase(list_of_ants.begin() + i);
        } else ++i;
    }
    spawn_ant(deltaTime);
    spawn_food(deltaTime);
    go_to_food();
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

            new_ant->add_new_subscriber(notification_manager);
        }
    }
}

void Anthill::update_food_count_text() const {
    food_count.setString("Food: " + std::to_string(food_quantity));
}

void Anthill::spawn_food(float deltaTime)
{
    last_food_spawn_time += deltaTime;

    if (last_food_spawn_time < Config::Food::spawn_interval) {
        return;
    }

    last_food_spawn_time = 0;

    if(current_count_food < Config::Food::max_count_of_food)
    {
        const auto new_food = new Food();
        DrawableEntity* new_food_render = new FoodRender(*new_food);
        render_manager_.addDrawable(new_food_render);

        current_count_food++;
        foods.push_back(new_food);
    }
    // заспавнилась еда, нужно собрать ее
}

void Anthill::go_to_food() {
    for (const auto food_ : foods) {
        if (food_->getState() != FoodState::free)
            continue;
        for (auto& ant : list_of_ants) {
            if (ant->get_state() == State::free && ant->getRole() == Collector) {
                ant->set_state(State::busy);
                food_->setState(FoodState::wait);
                ant->setTarget(food_->getX(), food_->getY());
                return ;
            }
        }
    }
}
