#include <iostream>
#include "models/Ant.h"
#include "models/Anthill.h"

int main(int argc, char *argv[]) {
    Ant a1, a2, a3, a4, a5;
    a1.updateAge();
    a1.updateAge();
    a1.updateAge();

    a2.updateAge();
    a2.updateAge();

    a3.updateAge();

    Anthill anthill;
    anthill.add_ant(a1);
    anthill.add_ant(a2);
    anthill.add_ant(a3);
    anthill.add_ant(a4);
    // anthill.add_ant(a5);

    anthill.print();

    for (unsigned i = 0; i < 13; ++i) {
        std::cout << "Iteration of " << i << std::endl;
        anthill.update();
        anthill.print();
        std::cout << std::endl;
    }

    return 0;
}
