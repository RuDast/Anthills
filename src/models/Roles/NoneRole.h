#ifndef NONEROLE_H
#define NONEROLE_H
#include "../Role.h"


class NoneRole : public Role { // TODO make class final
    void work() override;

public:
    ~NoneRole() override;
    void print() override;
};

inline Role* None = new NoneRole;

#endif //NONEROLE_H
