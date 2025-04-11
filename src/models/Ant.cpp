#include "Ant.h"
#include <iostream>
#include <set>

#include "Roles/NannyRole.h"
#include "Roles/NoneRole.h"

Ant::Ant() : age(0), health(100), role(None) {
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

void Ant::updateAge() {
    if (age < ANT_MAX_AGE) {
        ++age;
        updateRole();
    }
    if (age == ANT_MAX_AGE)
        terminate();
}

void Ant::terminate() {
    std::cout << "Ant is died." << std::endl;
    role = new NoneRole;
    // TODO уничтожить муравья.
}

void Ant::updateRole() {
    switch (age) {
        case NANNY_AGE:
            setRole(Nanny);
        break;
        // case SOLIDER_AGE:
        //     break;
            // TODO доделать
        default:
            break;
    }
}

bool Ant::getAlive() const {
    return age < ANT_MAX_AGE;
}

