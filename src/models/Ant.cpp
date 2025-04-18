#include "Ant.h"
#include <cmath>
#include <iostream>
#include "Anthill.h"
#include "Food.h"
#include "../constants.h"
#include "Roles/CleanerRole.h"
#include "Roles/CollectorRole.h"
#include "Roles/NannyRole.h"
#include "Roles/NoneRole.h"
#include "Roles/SoliderRole.h"
#include "informers/AntListener.h"
#include "informers/NotificationListener.h"


Ant::Ant(const float x, const float y) : age(Config::Ant::start_age),
                                         health(Config::Ant::max_health),
                                         role(None),
                                         x(x),
                                         y(y),
                                         target_x(x),
                                         target_y(y) {
}

void Ant::kill()
{
    health = 0;
    terminate();
}

void Ant::print() const {
    std::cout << "Age: " << age << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "Role: ";
    role->print();
}

void Ant::setRole(Role *new_role) {
    if (role != new_role) {
        need_to_move = true;
        role = new_role;
        for (const auto &sub: render_subscribers) {
            sub->on_change_role(*this);
        }
    }
}

Role *Ant::getRole() const {
    return role;
}

void Ant::updateAge(const float deltaTime) {
    last_update_time += deltaTime;

    if (last_update_time >= Config::Ant::age_update_time_interval) {
        ++age;
        last_update_time = 0;
        updateRole();
    }

    if (age >= Config::Ant::max_age || health <= 0) {
        terminate();
    }
}

void Ant::terminate() {
    if (anthill) {
        anthill->addCorpse(new Corpse(x, y));
    }
    in_trashzone = true;
    // for (auto sub : render_subscribers)
    // {
    //     sub->on_change_role(*this);
    // }
}

void Ant::updateRole() {
    switch (age) {
        case Config::Ant::nanny_age:
            setRole(Nanny);
            break;

        case Config::Ant::soldier_age:
            setRole(Soldier);
            break;

        case Config::Ant::collector_age:
            setRole(Collector);
            break;

        case Config::Ant::cleaner_age:
            setRole(Cleaner);
            break;

        default:
            break;
    }
}


bool Ant::isAlive() const {
    return age < Config::Ant::max_age && health > Config::Ant::start_age;
}

void Ant::setTarget(const float x, const float y) {
    target_x = x;
    target_y = y;
}

void Ant::update(const float deltaTime) {
    if (!isAlive())
        return;

    updateAge(deltaTime);

    // if (anthill && state == State::free && getRole()->isCleaner())
    //     anthill->go_to_corpse();

    // if (need_to_move && state == State::free && getRole() != None) {
    //     need_to_move = false;
    //     // setTarget(rand() % 1200, rand() % 800);
    // }

    float delta_x = target_x - x;
    float delta_y = target_y - y;
    float distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);

    // std::cout << "[DBG] Ant " << this
    //         << " state=" << int(state)
    //         << " pos=(" << x << "," << y << ")"
    //         << " target=(" << target_x << "," << target_y << ")"
    //         << " dist=" << distance
    //         << "\n";

    if (state == State::free && need_to_move && !getRole()->isNone()) {
        // новая случайная цель
        target_x = static_cast<float>(std::rand()) / RAND_MAX * Config::window_width;
        target_y = static_cast<float>(std::rand()) / RAND_MAX * Config::window_height;
        need_to_move = false;
        // std::cout << "[WANDER] Ant " << this
        //           << " moving to (" << target_x << ", " << target_y << ")\n";
    }

    if (distance < Config::EPSILON && state == State::free) {
        need_to_move = true;  // достигли — скоро выберем новую цель
    }

    // … ранее в методе вычислили distance …
    else if (distance < Config::EPSILON) {
        // Доставка еды на склад
        if (state == State::going && carried_food) {
            carried_food->setState(FoodState::on_sklad);
            if (anthill) anthill->addDeliveredFood();
            carried_food = nullptr;
            state = State::free;
            need_to_move = true; // Важно: освобождаем муравья

        }
        // Доставка трупа на мусорку
        // Подбор еды
        else if (state == State::busy && carried_food) {
            state = State::going;
            carried_food->terminate();
            carried_food->setState(FoodState::going);
            setTarget(Config::Anthill::sklad_x, Config::Anthill::sklad_y);

        } else if (state == State::busy && getRole()->isCleaner()) {
            std::cout << "[DEBUG] Cleaner " << this
                    << " picked up corpse at (" << x << "," << y << ")\n";
            state = State::going;
            carried_corpse->setState(CorpseState::going);
            carried_corpse->terminate();
            // Назначаем цель – свалка
            setTarget(Config::Anthill::trash_x, Config::Anthill::trash_y);
        }
        // Доставка трупа на мусорку
        else if (state == State::going && getRole()->isCleaner()) {
            std::cout << "[DEBUG] Cleaner " << this
                    << " delivered corpse to trash at (" << x << "," << y << ")\n";
            carried_corpse->setState(CorpseState::on_trash);
            carried_corpse = nullptr;
            state = State::free;
            // сразу ищем следующий труп
            std::cout << "ОТНЕС ТРУП!!!!" << std::endl;
        }
        // Подбор трупа
    }

    delta_x = target_x - x;
    delta_y = target_y - y;
    distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);

    // Движение к цели
    if (distance > Config::EPSILON) {
        const float vector_x = delta_x / distance;
        const float vector_y = delta_y / distance;
        float step = Config::Ant::speed * deltaTime;
        x += vector_x * std::min(step, distance);
        y += vector_y * std::min(step, distance);
    }
}

float Ant::getX() const {
    return x;
}

float Ant::getY() const {
    return y;
}

float Ant::getTargetX() const {
    return target_x;
}

float Ant::getTargetY() const {
    return target_y;
}

void Ant::add_subscriber(AntListener *sub) {
    render_subscribers.push_back(sub);
}

void Ant::lower_health(const int damage) {
    health -= damage;
    if (health <= Config::Ant::start_age) {
        terminate();
    }
}

void Ant::increase_health(const int health) {
    this->health += health;
    if (this->health > Config::Ant::max_age)
        this->health = Config::Ant::max_age;
}

void Ant::add_new_subscriber(NotificationListener *manager) {
    subs.push_back(manager);
}

void Ant::help_with_food() {
    for (auto &sub: subs) {
        sub->onFoodPickupFailed(*this);
    }
}

void Ant::set_state(State state) {
    if (state != this->state)
        this->state = state;
}

State Ant::get_state() const {
    return state;
}

void Ant::set_food(Food *food) {
    carried_food = food;
}

void Ant::set_anthill(Anthill *anthill) {
    this->anthill = anthill;
}


bool Ant::get_trash() const {
    return !in_trashzone;
}

void Ant::setCorpse(Corpse *c) {
    carried_corpse = c;
}
