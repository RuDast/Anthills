#include "Anthill.h"

Anthill::Anthill() {
    size = default_size_of_anthill;
    food_quantity = 0;
}

bool Anthill::add_ant(Ant &ant) {
    if (size >= max_anthill_size) {
        return false;
    }
    list_of_ants.push_back(&ant);
    return true;
}

void Anthill::update(const float deltaTime) {
    for (unsigned i = 0; i < list_of_ants.size();) {
        list_of_ants[i]->updateAge(deltaTime);
        if (!list_of_ants[i]->isAlive()) {
            list_of_ants.erase(list_of_ants.begin() + i);
        } else ++i;
    }
}

void Anthill::print() const {
    for (const auto &ant : list_of_ants) {
        ant->print();
    }
}

