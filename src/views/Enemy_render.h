#ifndef ENEMY_RENDER_H
#define ENEMY_RENDER_H

#include <SFML/Graphics.hpp>

#include "DrawableEntity.h"
#include "../models/Enemy.h"

class EnemyRender : public DrawableEntity {
    const Enemy& enemy;
    sf::CircleShape shape;

public:
    EnemyRender(const Enemy& enemy, float radius, const sf::Color& color);

    void update();
    // void draw(sf::RenderTarget& target) const;

    void draw(sf::RenderWindow &window) override;

    bool isAlive() override;
};

#endif // ENEMY_RENDER_H