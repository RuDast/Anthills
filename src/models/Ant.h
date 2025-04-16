#ifndef ANT_H
#define ANT_H
#include <vector>
#include "Role.h"
#include "informers/AntListener.h"
#include "informers/NotificationListener.h"
#include "informers/NotificationManager.h"

enum class State {
    free,
    busy,
    wait,
};


class Ant {
public:
    Ant(float x, float y);

private:
    unsigned age;
    short health;
    Role *role;

    bool need_to_move = true;
    float x, y;
    float target_x, target_y;
    std::vector<AntListener *> render_subscribers;
    float last_update_time = 0.0f;

    std::vector<NotificationListener*> subs;

    State state = State::free;

public:
    void print() const;

    void setRole(Role *new_role);

    Role *getRole() const;

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

    void add_subscriber(AntListener *sub);

    void lower_health(int damage);

    void increase_health(int health);

    void add_new_subscriber(NotificationListener* manager);

    void help_with_food();

    void set_state(State state);

    State get_state() const;
};


#endif //ANT_H
