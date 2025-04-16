#include "Enemy.h"

Enemy::Enemy(float start_x, float start_y)
    : x(start_x), y(start_y),
    min_y(0), max_y(800), moving_down(true) {
}

void Enemy::update(float delta_time) {
    // x -= speed * delta_time * 50.0f;

    if (moving_down) {
        y += speed * delta_time;
        if (y >= max_y) moving_down = false;
    }
    else {
        y -= speed * delta_time;
        if (y <= min_y) moving_down = true;
    }
}