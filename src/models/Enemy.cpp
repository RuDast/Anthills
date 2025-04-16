#include "Enemy.h"

Enemy::Enemy(float start_x, float start_y, float speed, float move_range)
    : x(start_x), y(start_y), speed(speed), move_range(move_range),
    min_y(start_y - move_range), max_y(start_y + move_range),
    moving_down(true) {
}

void Enemy::update(float delta_time) {
    x -= speed * delta_time * 50.0f;

    if (moving_down) {
        y += speed * delta_time * 30.0f;
        if (y >= max_y) moving_down = false;
    }
    else {
        y -= speed * delta_time * 30.0f;
        if (y <= min_y) moving_down = true;
    }
}