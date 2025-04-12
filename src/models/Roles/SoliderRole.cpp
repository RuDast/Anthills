#include "SoliderRole.h"
#include <iostream>

void SoliderRole::work() {
    std::cout << "Переопределение work для SoliderRole" << std::endl;
}

SoliderRole::~SoliderRole() = default;

void SoliderRole::print() {
    std::cout << "Solider" << std::endl;
}
