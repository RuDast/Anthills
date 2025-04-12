#include "CleanerRole.h"
#include <iostream>

void CleanerRole::work() {
    std::cout << "Переопределение work для CleanerRole" << std::endl;
}

CleanerRole::~CleanerRole() = default;

void CleanerRole::print() {
    std::cout << "Cleaner" << std::endl;
}
