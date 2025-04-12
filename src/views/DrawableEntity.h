#ifndef DRAWABLEENTITY_H
#define DRAWABLEENTITY_H
#include <SFML/Graphics/RenderWindow.hpp>


class DrawableEntity {
public:
    virtual ~DrawableEntity() = default;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual bool isAlive() = 0;
};


#endif //DRAWABLEENTITY_H
