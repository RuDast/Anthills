#include "Food.h"
#include <iostream>

Food::Food(): weight(1 + rand() % 2), x(rand() % 100), y(rand() % 740) {
}

void Food::print() const {
    std::cout << "Crumble is created" << std::endl << "X = " << x << "   Y = " << y << "\t Weight is : " << weight <<
            std::endl;
}

float Food::getX() const {
    return x;
}

float Food::getY() const {
    return y;
}

FoodState Food::getState() const {
    return state;
}

void Food::setState(const FoodState state) {
    this->state = state;
}

bool Food::isAlive() const {
    return is_alive;
}

void Food::terminate() {
    is_alive = false;
}

