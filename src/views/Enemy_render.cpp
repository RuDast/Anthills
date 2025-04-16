#include "enemy_render.h"

EnemyRender::EnemyRender(const Enemy& enemyRef)
    : enemy(enemyRef), shape(20.0f) {
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(20.0f, 20.0f);
    update();
}

void EnemyRender::update() {
    shape.setPosition(enemy.getX(), enemy.getY());
}

void EnemyRender::draw(sf::RenderWindow& window) const {
    if (enemy.isAlive()) {
        window.draw(shape);
    }
}