#ifndef ANTRENDER_H
#define ANTRENDER_H
#include <SFML/Graphics/Sprite.hpp>

#include "DrawableEntity.h"
#include "../models/Ant.h"


class AntRender : public DrawableEntity {
public:
    AntRender(const Ant &ref);
    ~AntRender() override;

private:
    const Ant &ant_;
    sf::Sprite sprite_;
    float x = 0, y = 0;

public:
    bool isAlive() override;
    void draw(sf::RenderWindow &window) override;
};


#endif //ANTRENDER_H
