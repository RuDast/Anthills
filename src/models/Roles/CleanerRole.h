#ifndef CLEANERROLE_H
#define CLEANERROLE_H
#include "../Role.h"


class CleanerRole : public Role {
    void work() override;

public:
    ~CleanerRole() override;

    void print() override;

    bool isCleaner() override;
};

/**
 *
 */
extern Role* Cleaner;
// Role *Cleaner = new CleanerRole;


#endif //CLEANERROLE_H
