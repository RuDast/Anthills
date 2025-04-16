#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "src/constants.h"
#include "src/Loader.h"
#include "src/models/Ant.h"
#include "src/models/Anthill.h"
#include "src/models/Enemy.h"
#include "src/views/AntRender.h"
#include "src/views/EnemyRender.h"
#include "src/views/RenderManager.h"
#include "src/views/TextureManager.h"

int main() {
    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(Config::window_width, Config::window_height),
        "Anthill",
        sf::Style::Titlebar | sf::Style::Close);

    // Загрузка текстур
    sf::Texture trash_texture, storage_texture, ant_spawn_texture, background_texture;
    if (load_textures(trash_texture, storage_texture, ant_spawn_texture, background_texture) != 0)
        return -1;

    // Создание игровых объектов
    sf::RectangleShape background(sf::Vector2f(Config::window_width, Config::window_height));
    background.setTexture(&background_texture);

    sf::RectangleShape storage(sf::Vector2f(200, 150));
    storage.setTexture(&storage_texture);

    sf::RectangleShape trash(sf::Vector2f(200, 150));
    trash.setTexture(&trash_texture);

    sf::RectangleShape spawn_of_ants(sf::Vector2f(400, 75));
    spawn_of_ants.setTexture(&ant_spawn_texture);

    sf::RectangleShape spawn_of_food(sf::Vector2f(200, 800));
    spawn_of_food.setFillColor(sf::Color(102, 102, 0));
    spawn_of_food.setOutlineThickness(4.f);
    spawn_of_food.setOutlineColor(sf::Color(102, 102, 0));

    // Пунктирная линия
    sf::VertexArray dashedLine(sf::Lines);
    sf::Color lineColor = sf::Color(172, 124, 61);
    for (float y = 0; y < 800; y += 15 + 10) {
        dashedLine.append(sf::Vertex(sf::Vector2f(600, y), lineColor));
        dashedLine.append(sf::Vertex(sf::Vector2f(600, std::min(y + 15, 800.0f)), lineColor));
    }

    // Позиционирование объектов
    spawn_of_ants.setPosition(800, 0);
    storage.setPosition(600, 0);
    trash.setPosition(600, 650);
    spawn_of_food.setPosition(0, 0);

    // Менеджер рендеринга
    RenderManager render_manager;

    // Шрифт и текст
    sf::Clock clock;
    sf::Font KaaosPro;
    KaaosPro.loadFromFile("../resources/fonts/KaaosPro.ttf");
    sf::Text food_count;
    food_count.setString("Food");
    food_count.setFont(KaaosPro);
    food_count.setCharacterSize(40);

    // Муравейник и первый муравей
    Anthill anthill(render_manager, food_count);
    Ant* ant = new Ant(100, 100);
    AntRender* ant_render = new AntRender(*ant);
    ant->add_subscriber(ant_render);
    render_manager.addDrawable(ant_render);
    anthill.update_food_count_text();
    anthill.add_ant(ant);

    // Система врагов
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<EnemyRender>> enemy_renders;
    sf::Clock enemy_spawn_timer;

    // Главный игровой цикл
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Спавн врагов
        if (enemy_spawn_timer.getElapsedTime().asSeconds() > 5.0f) {
            auto enemy = std::make_unique<Enemy>(
                Config::window_width + 50,
                rand() % (Config::window_height - 100) + 50,
                1.5f,   // speed
                100.0f  // move range
            );

            auto render = std::make_unique<EnemyRender>(*enemy, 25.0f, sf::Color::Red);

            render_manager.addDrawable(render.get());
            enemies.push_back(std::move(enemy));
            enemy_renders.push_back(std::move(render));

            enemy_spawn_timer.restart();
        }

        // Обновление игры
        anthill.update(deltaTime);

        // Обновление врагов
        for (size_t i = 0; i < enemies.size(); ) {
            enemies[i]->update(deltaTime);

            if (enemies[i]->getX() < -50) {
                render_manager.removeDrawable(enemy_renders[i].get());
                enemies.erase(enemies.begin() + i);
                enemy_renders.erase(enemy_renders.begin() + i);
            }
            else {
                enemy_renders[i]->update();
                i++;
            }
        }

        // Отрисовка
        window.clear();

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

    // Очистка памяти
    delete ant;
    delete ant_render;

    return 0;
}