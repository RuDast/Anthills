#include "Role.h"
#include <iostream>

void Role::print() {
    std::cout << "Роль муравья" << std::endl;
}

bool Role::isCleaner() {
    return false;
}

bool Role::isNone() {
    return false;
}
