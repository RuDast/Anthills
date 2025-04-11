#include "NannyRole.h"
#include <iostream>

void NannyRole::work() {
    std::cout << "Переопределение work для NannyRole" << std::endl;
}

NannyRole::~NannyRole() = default;

void NannyRole::print() {
    std::cout << "Nanny" << std::endl;
}
