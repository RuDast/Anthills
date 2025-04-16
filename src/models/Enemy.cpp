#include "Enemy.h"

Enemy::Enemy(float startX, float startY)
    : x(startX), y(startY), speed(100.0f), health(100.0f) {
}

void Enemy::update(float deltaTime) {
    // Движение к муравейнику (влево)
    x -= speed * deltaTime;
}

void Enemy::takeDamage(float damage) {
    health -= damage;
}

bool Enemy::isAlive() const {
    return health > 0;
}

float Enemy::getX() const { return x; }
float Enemy::getY() const { return y; }