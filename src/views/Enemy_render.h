#ifndef ENEMY_RENDER_H
#define ENEMY_RENDER_H
#include <SFML/Graphics/Sprite.hpp>


#include "DrawableEntity.h"
#include "../models/Enemy.h"



class EnemyRender : public DrawableEntity
{
public:
    EnemyRender(const Enemy& enemy);
    ~EnemyRender() override;
private:
    const Enemy& enemy_;
    sf::Sprite sprite_;
    float x, y;
public:



    void update();

    void draw(sf::RenderWindow &window) override;

    bool isAlive() override;
};

#endif // ENEMY_RENDER_H