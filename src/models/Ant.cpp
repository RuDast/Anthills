#include "Ant.h"

#include <cmath>
#include <iostream>

#include "Roles/CleanerRole.h"
#include "Roles/CollectorRole.h"
#include "Roles/NannyRole.h"
#include "Roles/NoneRole.h"
#include "Roles/SoliderRole.h"

#define EPSILON 0.001

Ant::Ant(const float x, const float y) : age(0), health(100), role(None), x(x), y(y), target_x(x), target_y(y) {
}

void Ant::print() const {
    std::cout << "Age: " << age << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "Role: ";
    role->print();
}

void Ant::setRole(Role *new_role) {
    if (role != new_role)
        role = new_role;
}

Role *Ant::getRole() const {
    return role;
}

void Ant::updateAge(const float deltaTime) {
    last_update_time += deltaTime;

    if (last_update_time >= age_update_time_interval) {
        ++age;
        last_update_time = 0;
        updateRole();
    }

    if (age >= ANT_MAX_AGE)
        terminate();
}

void Ant::terminate() {
    std::cout << "Ant is died." << std::endl;
    role = None;
}

void Ant::updateRole() {
    switch (age) {
        case NANNY_AGE:
            std::cout << "The ant became a nanny." << std::endl;
            setRole(Nanny);
        break;
        case SOLIDER_AGE:
             std::cout << "The ant became a solider." << std::endl;
             setRole(Solider);
        break;
        case COLLECTOR_AGE:
            std::cout << "The ant became a collector." << std::endl;
            setRole(Collector);
        break;
        case CLEANER_AGE:
            std::cout << "The ant became a cleaner." << std::endl;
            setRole(Cleaner);
        break;
        default:
            break;
    }
}

bool Ant::isAlive() const {
    return age < ANT_MAX_AGE;
}

void Ant::setTarget(const float x, const float y) {
    target_x = x;
    target_y = y;
}

void Ant::update(const float deltaTime) {
    if (!isAlive())
        return ;
    const float delta_x = target_x - x;
    const float delta_y = target_y - y;
    const float distance = sqrt(delta_x * delta_x + delta_y * delta_y);

    if (distance < EPSILON)
        return;

    const float vector_x = delta_x / distance;
    const float vector_y = delta_y / distance;

    float step = speed * deltaTime;
    if (step > distance)
        step = distance;

    x += vector_x * step;
    y += vector_y * step;

    updateAge(deltaTime);
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

