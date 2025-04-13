#include <SFML/Graphics.hpp>

#include "src/models/Ant.h"
#include "src/views/AntRender.h"
#include "src/views/RenderManager.h"
#include "src/views/TextureManager.h"

int main()
{
    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Anthill");

    sf::RectangleShape background(sf::Vector2f(1200, 800));
    background.setFillColor(sf::Color(128, 128, 128));

    sf::RectangleShape storage(sf::Vector2f(200,150)); // склад с едой
    storage.setFillColor(sf::Color(102,102,102));

    sf::RectangleShape trash(sf::Vector2f(200,150)); // мусорка
    trash.setFillColor(sf::Color(129,104,65));

    TextureManager::getInstance().loadTexture("common_ant", "../resources/ants/common_ant.png");
    TextureManager::getInstance().loadTexture("solider_ant", "../resources/ants/coleader_ant.png");
    TextureManager::getInstance().loadTexture("collector_ant", "../resources/ants/collector_ant.png");
    TextureManager::getInstance().loadTexture("cleaner_ant", "../resources/ants/cleaner_ant.png");


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

        storage.setPosition(600,0);
        window.draw(storage);

        trash.setPosition(600, 650);
        window.draw(trash);

        render_manager.drawAll(window);
        window.display();
    }


    ant.print();
    return 0;
}
