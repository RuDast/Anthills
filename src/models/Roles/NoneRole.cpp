#include "NoneRole.h"

#include <iostream>

void NoneRole::work() {
    std::cout << "Переопределение work для NoneRole" << std::endl;
}

NoneRole::~NoneRole() = default;

void NoneRole::print() {
    std::cout << "None" << std::endl;
}
