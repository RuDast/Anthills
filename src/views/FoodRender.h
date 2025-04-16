#ifndef FOODRENDER_H
#define FOODRENDER_H

#include <SFML/Graphics/Sprite.hpp>

#include "DrawableEntity.h"
#include "../models/Food.h"


class FoodRender : public DrawableEntity
{
public:
    FoodRender(const Food& food);
    ~FoodRender() override;
private:
    const Food& food_;
    sf::Sprite sprite_;
    float x, y;
public:
    void draw(sf::RenderWindow &window) override;

    bool isAlive() override;
};



#endif //FOODRENDER_H