#ifndef ANT_H
#define ANT_H
#include <vector>

#include "Role.h"
#include "informers/AntListener.h"

enum {
    ANT_MAX_AGE = 13,
    NANNY_AGE = 2,
    SOLIDER_AGE = 5,
    COLLECTOR_AGE = 8,
    CLEANER_AGE = 10
};


class Ant {
public:
    Ant(float x, float y);

private:
    unsigned age;
    unsigned health;
    Role *role;

    bool need_to_move = false;
    float x, y;
    float target_x, target_y;
    float angle = 0;
<<<<<<< HEAD
    const float speed = 500;
    std::vector<AntListener*> subscribers;
    float last_update_time = 0.0f;
    const float age_update_time_interval = 0.5f;
=======
    const float speed = 50;

    float last_update_time = 0.0f;
    const float age_update_time_interval = 1.0f;
>>>>>>> origin/roles
public:
    void print() const;
    void setRole(Role *new_role);
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
};


#endif //ANT_H
