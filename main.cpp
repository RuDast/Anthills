#include <iostream>
#include <SFML/Graphics.hpp>

#include "src/constants.h"
#include "src/Loader.h"
#include "src/models/Ant.h"
#include "src/models/Anthill.h"
#include "src/models/Enemy.h"
#include "src/models/informers/NotificationManager.h"
#include "src/views/AntRender.h"
#include "src/views/enemy_render.h"
#include "src/views/RenderManager.h"
#include "src/views/TextureManager.h"

int main() {
    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(Config::window_width, Config::window_height),
                            "Anthill",
                            sf::Style::Titlebar | sf::Style::Close);

    sf::Texture trash_texture, storage_texture, ant_spawn_texture, background_texture, spawn_of_food_texture, flower_texture, bush_texture;
    if (load_textures(trash_texture, storage_texture, ant_spawn_texture, background_texture, spawn_of_food_texture, flower_texture, bush_texture) != 0)
        return -1;


    sf::RectangleShape background(sf::Vector2f(Config::window_width, Config::window_height));
    background.setTexture(&background_texture);

    sf::RectangleShape storage(sf::Vector2f(200, 150)); // склад с едой
    storage.setTexture(&storage_texture);

    sf::RectangleShape trash(sf::Vector2f(200, 150)); // мусорка
    trash.setTexture(&trash_texture);

    sf::RectangleShape spawn_of_ants(sf::Vector2f(400, 75)); // спавн
    spawn_of_ants.setTexture(&ant_spawn_texture);

    sf::RectangleShape spawn_of_food(sf::Vector2f(200, 800));
    spawn_of_food.setTexture(&spawn_of_food_texture);

    std::vector<sf::RectangleShape> flowers;

    for (int i = 0; i < 30; ++i) {
        sf::RectangleShape flower(sf::Vector2f(35, 35)); // Размер цветка
        flower.setTexture(&flower_texture);
        flower.setPosition(rand() % 1200 + 200, rand() % 800);
        flowers.push_back(flower);
    }

    std::vector<sf::RectangleShape> bushes;

    for (int i = 0; i < 15; ++i) {
        sf::RectangleShape bush(sf::Vector2f(50, 50));
        bush.setTexture(&bush_texture);
        bush.setPosition(rand() % 1200 + 200, rand() % 800);
        flowers.push_back(bush);
    }



    spawn_of_ants.setPosition(780, 0);
    storage.setPosition(600, 0);
    trash.setPosition(600, 650);
    spawn_of_food.setPosition(0, 0);

    RenderManager render_manager;

    sf::Clock clock;
    sf::Font KaaosPro;
    KaaosPro.loadFromFile("../resources/fonts/KaaosPro.ttf");
    sf::Text food_count;
    food_count.setString("Food");
    food_count.setFont(KaaosPro);
    food_count.setCharacterSize(40);


    NotificationListener *notification_manager = new NotificationManager();
    Anthill anthill(render_manager, food_count, notification_manager);
    notification_manager->connectAnthill(&anthill);
    anthill.update_food_count_text();

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        anthill.update(deltaTime);


        window.draw(background);
        window.draw(spawn_of_food);
        for (const auto& flower : flowers) {
            window.draw(flower);
        }

        for (const auto& bush : bushes) {
            window.draw(bush);
        }
        window.draw(spawn_of_ants);
        window.draw(storage);
        window.draw(trash);

        window.draw(food_count);
        render_manager.drawAll(window);
        window.display();
    }

    return 0;
}
