#include "FoodRender.h"
#include "../models/Food.h"
#include "TextureManager.h"
#include <iostream>

FoodRender::FoodRender(const Food& food): food_(food)
{
    sprite_.setTexture(TextureManager::getInstance().getTexture("food"));
}


void FoodRender::draw(sf::RenderWindow &window)
{
    const float X = food_.getX();
    const float Y = food_.getY();

    sprite_.setPosition(X,Y);
    window.draw(sprite_);
}

bool FoodRender::isAlive()
{
    return food_.isAlive();
}


FoodRender::~FoodRender()
{

}
