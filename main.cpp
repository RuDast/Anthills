#include <SFML/Graphics.hpp>

#include "src/models/Ant.h"
#include "src/views/AntRender.h"
#include "src/views/RenderManager.h"
#include "src/views/TextureManager.h"

int main()
{
    sf::Texture trash_texture;
    trash_texture.loadFromFile(("../resources/textures/trash_texture.png"));

    sf::Texture storage_texture;
    storage_texture.loadFromFile("../resources/textures/storage_texture.png");

    sf::Texture ant_spawn_texture;
    ant_spawn_texture.loadFromFile("../resources/textures/ant_spawn_textures.png");

    sf::Texture background_texture;
    background_texture.loadFromFile("../resources/textures/dirt.png");


    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Anthill");

    sf::RectangleShape background(sf::Vector2f(1200, 800));
    background.setTexture(&background_texture);


    sf::RectangleShape storage(sf::Vector2f(200, 150)); // склад с едой
    storage.setTexture(&storage_texture);


    TextureManager::getInstance().loadTexture("common_ant", "../resources/ants/common_ant.png");
    TextureManager::getInstance().loadTexture("solider_ant", "../resources/ants/coleader_ant.png");
    TextureManager::getInstance().loadTexture("collector_ant", "../resources/ants/collector_ant.png");
    TextureManager::getInstance().loadTexture("cleaner_ant", "../resources/ants/cleaner_ant.png");

    sf::RectangleShape trash(sf::Vector2f(200, 150)); // мусорка
    trash.setTexture(&trash_texture);

    sf::RectangleShape spawn_of_ants(sf::Vector2f(400, 75)); //спавн
    spawn_of_ants.setTexture(&ant_spawn_texture);

    sf::RectangleShape spawn_of_food(sf::Vector2f(200, 800));
    spawn_of_food.setFillColor(sf::Color(102,102,0));
    spawn_of_food.setOutlineThickness(4.f);
    spawn_of_food.setOutlineColor(sf::Color(102,102,0));

    sf::VertexArray dashedLine(sf::Lines);
    sf::Color lineColor = sf::Color(172, 124, 61);
  
    for (float y = 0; y < 800; y += 15 + 10) {
        dashedLine.append(sf::Vertex(sf::Vector2f(600, y), lineColor));
        dashedLine.append(sf::Vertex(sf::Vector2f(600, std::min(y + 15, 800.0f)), lineColor));
    }

    spawn_of_ants.setPosition(800,0);
    storage.setPosition(600,0);
    trash.setPosition(600, 650);
    spawn_of_food.setPosition(0,0);

    RenderManager render_manager;
    Ant ant(rand() % 1200, rand() % 800);
    Ant ant2(rand() % 1200, rand() % 800);
    Ant ant3(rand() % 1200, rand() % 800);
    Ant ant4(rand() % 1200, rand() % 800);

    AntRender *ant_render = new AntRender(ant);
    ant.add_subscriber(ant_render);
    render_manager.addDrawable(ant_render);

    AntRender *ant_render2 = new AntRender(ant2);
    ant2.add_subscriber(ant_render2);
    render_manager.addDrawable(ant_render2);

    AntRender *ant_render3 = new AntRender(ant3);
    ant3.add_subscriber(ant_render3);
    render_manager.addDrawable(ant_render3);
    AntRender *ant_render4 = new AntRender(ant4);
    ant4.add_subscriber(ant_render4);
    render_manager.addDrawable(ant_render4);

    sf::Clock clock;
    ant.setTarget(rand() % 1200, rand() % 800);
    ant2.setTarget(rand() % 1200, rand() % 800);
    ant3.setTarget(rand() % 1200, rand() % 800);
    ant4.setTarget(rand() % 1200, rand() % 800);


    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ant.update(deltaTime);
        ant2.update(deltaTime);
        ant3.update(deltaTime);
        ant4.update(deltaTime);

        window.clear();

        window.draw(background);
        window.draw(spawn_of_ants);
        window.draw(storage);
        window.draw(trash);
        window.draw(spawn_of_food);
        window.draw(dashedLine);

        render_manager.drawAll(window);
        window.display();
    }


    ant.print();
    return 0;
}
