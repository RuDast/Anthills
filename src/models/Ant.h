#ifndef ANT_H
#define ANT_H
#include "Role.h"

enum {
    ANT_MAX_AGE = 13,
    NANNY_AGE = 2,
    SOLIDER_AGE = 5
};


class Ant {
public:
    Ant();

private:
    unsigned age;
    unsigned health;
    Role *role; // TODO после создания Role прикрутить его сюда
public:
    void print() const;
    void setRole(Role *new_role);
    Role* getRole() const;
    void updateAge();
    void terminate();
    void updateRole();
    bool getAlive() const;
};


#endif //ANT_H
