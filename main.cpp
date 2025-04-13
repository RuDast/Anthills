#include <SFML/Graphics.hpp>

#include "src/models/Ant.h"
#include "src/views/AntRender.h"
#include "src/views/RenderManager.h"
#include "src/views/TextureManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Anthill");

    sf::RectangleShape background(sf::Vector2f(1200, 800));
    background.setFillColor(sf::Color(128, 128, 128));

    sf::RectangleShape storage(sf::Vector2f(200,150)); //склад с едой
    storage.setFillColor(sf::Color(102,102,102));

    sf::RectangleShape trash(sf::Vector2f(200,150)); //мусорка
    trash.setFillColor(sf::Color(129,104,65));

    TextureManager::getInstance().loadTexture("common_ant", "../resources/ants/common_ant.png");

    // sf::Texture ant_texture;
    // ant_texture.loadFromFile("../resources/ants/common_ant.png"); // TODO нужно указывать путь относительно директории проекта, поэтому используем ..


    RenderManager render_manager;
    Ant ant(0, 800);
<<<<<<< HEAD

    AntRender *ant_render = new AntRender(ant, ant_texture);
    ant.add_subscriber(ant_render);
=======
    DrawableEntity *ant_render = new AntRender(ant);
>>>>>>> origin/roles
    render_manager.addDrawable(ant_render);

    sf::Clock clock;
    ant.setTarget(650, 100);
    ant.print();

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
