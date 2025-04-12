#ifndef COLLECTORROLE_H
#define COLLECTORROLE_H
#include "../Role.h"


class CollectorRole: public Role {
    void work() override;

public:
    ~CollectorRole() override;
    void print() override;
};

inline Role* Collector = new CollectorRole;


#endif //COLLECTORROLE_H