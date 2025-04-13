#ifndef ANTRENDER_H
#define ANTRENDER_H
#include <SFML/Graphics/Sprite.hpp>

#include "DrawableEntity.h"
#include "../models/Ant.h"
#include "../models/informers/AntListener.h"


class AntRender : public DrawableEntity, public AntListener {
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
    void on_change_role(const Ant &ant) override;
};


#endif //ANTRENDER_H
