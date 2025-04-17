#ifndef ANTHILL_H
#define ANTHILL_H
#include <vector>
#include <iostream>


#include "Ant.h"
#include <SFML/Graphics/Text.hpp>

#include "../constants.h"
#include "../views/RenderManager.h"
#include "Enemy.h"



class Anthill {
public:
    Anthill(RenderManager &render_manager,
            sf::Text &food_count_text);

private:
    unsigned int spawner_x[Config::Anthill::spawners_count] = {760, 800, 840, 880, 920, 960, 1000, 1040, 1080, 1120};
    unsigned short spawner_y = 100;
    bool free_spawners[Config::Anthill::spawners_count];
    Ant *ants_in_spawners[Config::Anthill::spawners_count];
    int food_quantity = 5000;
    unsigned size;
    std::vector<Ant *> list_of_ants;
    float last_spawn_time = 0;
    RenderManager &render_manager_;
    sf::Text &food_count;
    float last_age_update_time = 0;
    float last_food_spawn_time = 0;
    int current_count_food = 0;

public:
    bool add_ant(Ant *ant);

    void update(float deltaTime);

    void print() const;

    void spawn_ant(float deltaTime);

    void update_food_count_text() const;

    void spawn_food(float deltaTime);

};


#endif //ANTHILL_H
