#include "Ant.h"
#include <cmath>
#include <iostream>
#include "../constants.h"
#include "Roles/CleanerRole.h"
#include "Roles/CollectorRole.h"
#include "Roles/NannyRole.h"
#include "Roles/NoneRole.h"
#include "Roles/SoliderRole.h"
#include "informers/AntListener.h"


Ant::Ant(const float x, const float y) : age(Config::Ant::start_age),
                                         health(Config::Ant::max_health),
                                         role(None),
                                         x(x),
                                         y(y),
                                         target_x(x),
                                         target_y(y) {
}

void Ant::print() const {
    std::cout << "Age: " << age << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "Role: ";
    role->print();
}

void Ant::setRole(Role *new_role) {
    if (role != new_role) {
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

    if (age >= Config::Ant::max_age) {
        terminate();
    }
}

void Ant::terminate() {
    for (auto sub : render_subscribers)
    {
        sub->on_change_role(*this);
    }
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

    if (need_to_move && state == State::free && getRole() != None) {
        need_to_move = false;
        // setTarget(rand() % 1200, rand() % 800);
    }

    const float delta_x = target_x - x;
    const float delta_y = target_y - y;
    const float distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);

    if (distance < Config::EPSILON) {
        if (getRole() == Collector && state == State::busy && carried_food != nullptr) {
            state = State::going;
            carried_food->setState(FoodState::going);
            setTarget(Config::Anthill::sklad_x, Config::Anthill::sklad_y);
            carried_food->terminate();
        } else if (getRole() == Collector &&  state == State::going && carried_food != nullptr) {
            carried_food->setState(FoodState::on_sklad);
            if (anthill != nullptr) {
                anthill->addDeliveredFood();
            }
            carried_food = nullptr;
            state = State::free;
        }
        else if (getRole() == Cleaner && state == State::busy && died_ant != nullptr) {
            std::cout << "Ant has gone to died ant." << std::endl;
            state = State::going;
            died_ant->set_state(State::died);
            setTarget(Config::Anthill::trash_x, Config::Anthill::trash_y);
            died_ant->set_trash();
        }
        else if (getRole() == Cleaner && state == State::going && died_ant != nullptr) {
            std::cout << "Ant has gone to trash zone." << std::endl;
            died_ant->set_state(State::trash);
            died_ant = nullptr;
            state = State::free;
        }

        need_to_move = true;
        return;
    }

    const float vector_x = delta_x / distance;
    const float vector_y = delta_y / distance;

    float step = Config::Ant::speed * deltaTime;
    if (step > distance)
        step = distance;

    x += vector_x * step;
    y += vector_y * step;
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
    for (auto& sub : subs) {
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


bool Ant::get_trash() const
{
    return !in_trashzone;
}

void Ant::set_trash()
{
    in_trashzone = true;
}

void Ant::set_died_ant(Ant* died_ant)
{
    this->died_ant = died_ant;
}



