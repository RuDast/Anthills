#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include "views/TextureManager.h"

int load_textures(sf::Texture &trash_texture,
                  sf::Texture &storage_texture,
                  sf::Texture &ant_spawn_texture,
                  sf::Texture &background_texture, sf::Texture &spawn_of_food_texture, sf::Texture &flower_texture, sf::Texture &bush_texture) {
    if (!trash_texture.loadFromFile("../resources/textures/trash_texture.png")) {
        std::cerr << "Error of load texture" << std::endl;
        return -1;
    }

    if (!storage_texture.loadFromFile("../resources/textures/storage_texture.png")) {
        std::cerr << "Error of load texture" << std::endl;
        return -1;
    }

    if (!ant_spawn_texture.loadFromFile("../resources/textures/ant_spawn_textures.png")) {
        std::cerr << "Error of load texture" << std::endl;
        return -1;
    }

    if (!background_texture.loadFromFile("../resources/textures/dirt.png")) {
        std::cerr << "Error of load texture" << std::endl;
        return -1;
    }
    if (!spawn_of_food_texture.loadFromFile("../resources/textures/spawn_of_food_texture.png")) {
        std::cerr << "Error of load texture" << std::endl;
        return -1;
    }
    if (!flower_texture.loadFromFile("../resources/textures/flower_texture.png")) {
        std::cerr << "Error of load texture" << std::endl;
        return -1;
    }
    if (!bush_texture.loadFromFile("../resources/textures/bush_texture.png")) {
        std::cerr << "Error of load texture" << std::endl;
        return -1;
    }

    TextureManager::getInstance().loadTexture("common_ant", "../resources/ants/common_ant.png");
    TextureManager::getInstance().loadTexture("solider_ant", "../resources/ants/soldier_ant.png");
    TextureManager::getInstance().loadTexture("collector_ant", "../resources/ants/collector_ant.png");
    TextureManager::getInstance().loadTexture("cleaner_ant", "../resources/ants/cleaner_ant.png");
    TextureManager::getInstance().loadTexture("food", "../resources/food.png");
    return 0;
}
