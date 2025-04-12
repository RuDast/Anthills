#include "CollectorRole.h"
#include <iostream>

void CollectorRole::work() {
    std::cout << "Переопределение work для CollectorRole" << std::endl;
}

CollectorRole::~CollectorRole() = default;

void CollectorRole::print() {
    std::cout << "Collector" << std::endl;
}
