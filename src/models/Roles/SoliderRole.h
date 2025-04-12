#ifndef SOLIDERROLE_H
#define SOLIDERROLE_H
#include "../Role.h"


class SoliderRole: public Role {
    void work() override;

public:
    ~SoliderRole() override;
    void print() override;
};

inline Role* Solider = new SoliderRole;

#endif //SOLIDERROLE_H
