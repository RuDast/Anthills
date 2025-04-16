#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
private:
    float x, y;
    float speed;
    float health;

public:
    Enemy(float startX, float startY);
    void update(float deltaTime);
    void takeDamage(float damage);
    bool isAlive() const;

    float getX() const;
    float getY() const;
};

#endif // ENEMY_H