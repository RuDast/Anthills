#include <SFML/Graphics.hpp>

#include "src/models/Ant.h"
#include "src/views/AntRender.h"
#include "src/views/RenderManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Anthill");

    sf::RectangleShape background(sf::Vector2f(1200, 800));
    background.setFillColor(sf::Color(128, 128, 128));

    sf::Texture ant_texture;
    ant_texture.loadFromFile("resources/icon.png");

    RenderManager render_manager;
    Ant ant(0, 0);
    DrawableEntity *ant_render = new AntRender(ant, ant_texture);
    render_manager.addDrawable(ant_render);

    sf::Clock clock;
    ant.setTarget(300, 300);
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
        render_manager.drawAll(window);
        window.display();
    }


    ant.print();
    return 0;
}
