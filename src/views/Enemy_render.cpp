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

void EnemyRender::draw(sf::RenderTarget& target) const {
    target.draw(shape);
}