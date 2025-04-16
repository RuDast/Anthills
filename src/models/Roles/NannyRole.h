#ifndef NANNYROLE_H
#define NANNYROLE_H
#include "../Role.h"


class NannyRole : public Role {
    // TODO make class final
    void work() override;

public:
    ~NannyRole() override;

    void print() override;
};

inline Role *Nanny = new NannyRole;

#endif //NANNYROLE_H
