#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
private:
    float x, y;
    float speed = 100;
    float min_y, max_y;
    bool moving_down;

public:
    Enemy(float start_x, float start_y);
    void update(float delta_time);
    float getX() const 
    { 
        return x; 
    }

    float getY() const 
    { 
        return y; 
    }
};

#endif // ENEMY_H