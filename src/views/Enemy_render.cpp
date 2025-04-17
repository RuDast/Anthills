#include <iostream>

#include "enemy_render.h"

EnemyRender::EnemyRender(const Enemy& enemy, float radius, const sf::Color& color)
    : enemy(enemy), shape(radius) {
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
    update();
}

void EnemyRender::update() {
    shape.setPosition(enemy.getX(), enemy.getY());
}

// void EnemyRender::draw(sf::RenderTarget& target) const {
//     target.draw(shape);
// }

void EnemyRender::draw(sf::RenderWindow &window) {
    shape.setPosition(enemy.getX(), enemy.getY());
    //std::cout << enemy.getX() << ' ' << enemy.getY() << std::endl;
    window.draw(shape);
}

bool EnemyRender::isAlive() {
    return true;
}
