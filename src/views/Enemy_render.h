#ifndef ENEMY_RENDER_H
#define ENEMY_RENDER_H

#include <SFML/Graphics.hpp>
#include "../models/Enemy.h"

class EnemyRender {
private:
    const Enemy& enemy;
    sf::CircleShape shape;

public:
    EnemyRender(const Enemy& enemyRef);
    void update();
    void draw(sf::RenderWindow& window) const;
};

#endif // ENEMY_RENDER_H