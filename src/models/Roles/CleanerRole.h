#ifndef CLEANERROLE_H
#define CLEANERROLE_H
#include "../Role.h"


class CleanerRole: public Role {
    void work() override;

public:
    ~CleanerRole() override;
    void print() override;
};

inline Role* Cleaner = new CleanerRole;



#endif //CLEANERROLE_H
