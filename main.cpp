#include <iostream>
#include <SFML/Graphics.hpp>

#include "src/constants.h"
#include "src/Loader.h"
#include "src/models/Ant.h"
#include "src/models/Anthill.h"
#include "src/models/Enemy.h"
#include "src/views/AntRender.h"
#include "src/views/enemy_render.h"
#include "src/views/RenderManager.h"
#include "src/views/TextureManager.h"

int main() {
    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(Config::window_width, Config::window_height),
                            "Anthill",
                            sf::Style::Titlebar | sf::Style::Close);

    sf::Texture trash_texture, storage_texture, ant_spawn_texture, background_texture;
    if (load_textures(trash_texture, storage_texture, ant_spawn_texture, background_texture) != 0)
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
    spawn_of_food.setFillColor(sf::Color(102, 102, 0));
    spawn_of_food.setOutlineThickness(4.f);
    spawn_of_food.setOutlineColor(sf::Color(102, 102, 0));

    sf::VertexArray dashedLine(sf::Lines);
    sf::Color lineColor = sf::Color(172, 124, 61);

    for (float y = 0; y < 800; y += 15 + 10) {
        dashedLine.append(sf::Vertex(sf::Vector2f(600, y), lineColor));
        dashedLine.append(sf::Vertex(sf::Vector2f(600, std::min(y + 15, 800.0f)), lineColor));
    }

    spawn_of_ants.setPosition(800, 0);
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

    Anthill anthill(render_manager, food_count);
    anthill.update_food_count_text();

    // Enemy enemy(200, 200);
    // EnemyRender enemy_render(enemy, 20, sf::Color(128, 128, 128));
    // render_manager.addDrawable(&enemy_render);

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
        window.draw(spawn_of_ants);
        window.draw(storage);
        window.draw(trash);
        window.draw(spawn_of_food);
        window.draw(dashedLine);
        window.draw(food_count);

        render_manager.drawAll(window);
        window.display();
    }

    return 0;
}
