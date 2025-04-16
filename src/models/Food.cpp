#include "Food.h"
#include <iostream>

Food::Food(): x(rand() % 100), y(rand() % 800), weight(1+ (rand() % 2))
{}


void Food::print() const
{
    std::cout << "Crumble is created" <<std::endl << "X = " << x << "   Y = " << y << "\t Weight is : " << weight <<std::endl;

}

float Food::getX() const
{
    return x;
}

float Food::getY() const
{
    return x;
}