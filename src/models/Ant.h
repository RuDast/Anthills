#ifndef ANT_H
#define ANT_H
#include <vector>
#include "Role.h"
#include "informers/AntListener.h"
#include "Anthill.h"


class Ant {
public:
    Ant(float x, float y);

private:
    unsigned age;
    short health = 100;
    Role *role;
    bool in_trashzone = false;
    bool need_to_move = true;
    float x, y;
    float target_x, target_y;
    std::vector<AntListener*> subscribers;
    float last_update_time = 0.0f;

    bool alive = true;

public:
    void print() const;

    void setRole(Role* new_role);

    Role* getRole() const;

    void updateAge(float deltaTime);

    void terminate();

    void updateRole();

    bool isAlive() const;

    void setTarget(float x, float y);

    void update(float deltaTime);

    float getX() const;

    float getY() const;

    float getTargetX() const;

    float getTargetY() const;

    void add_subscriber(AntListener* sub);

    void lower_health(int damage);

    void increase_health(int health);

    bool get_trash() const;
};


#endif //ANT_H
