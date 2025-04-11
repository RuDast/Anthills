#ifndef ANTHILL_H
#define ANTHILL_H
#include <vector>
#include "Ant.h"

enum {
    default_size_of_anthill = 5,
    max_anthill_size = 20
};

class Anthill {
public:
    Anthill();

private:
    unsigned short food_quantity;
    unsigned size;
    std::vector<Ant*> list_of_ants;

public:
    bool add_ant(Ant& ant);
    void update();
    void print() const;
};


#endif //ANTHILL_H
