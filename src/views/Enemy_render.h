#ifndef ENEMY_RENDER_H
#define ENEMY_RENDER_H

#include <SFML/Graphics.hpp>
#include "../models/Enemy.h"

class EnemyRender {
private:
    const Enemy& enemy;
    sf::CircleShape shape;

public:
    EnemyRender(const Enemy& enemy, float radius, const sf::Color& color);
    void update();
    void draw(sf::RenderTarget& target) const;
};

#endif // ENEMY_RENDER_H