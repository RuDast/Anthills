#include "Food.h"
#include <iostream>

Food::Food(): weight(1 + rand() % 2), x(rand() % 100), y(rand() % 740)
{
}

void Food::print() const
{
    std::cout << "Crumble is created" << std::endl << "X = " << x << "   Y = " << y << "\t Weight is : " << weight <<
            std::endl;
}

float Food::getX() const
{
    return x;
}

float Food::getY() const
{
    return y;
}
