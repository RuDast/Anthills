#include <SFML/Graphics.hpp>

#include "src/models/Ant.h"
#include "src/views/AntRender.h"
#include "src/views/RenderManager.h"

int main()
{
    sf::Texture ant_texture;
    ant_texture.loadFromFile("../resources/ants/common_ant.png"); // TODO нужно указывать путь относительно директории проекта, поэтому используем ..

    sf::Texture trash_texture;
    trash_texture.loadFromFile(("../resources/textures/trash_texture.png"));

    sf::Texture storage_texture;
    storage_texture.loadFromFile("../resources/textures/storage_texture.png");

    sf::Texture ant_spawn_texture;
    ant_spawn_texture.loadFromFile("../resources/textures/ant_spawn_textures.png");

    sf::Texture background_texture;
    background_texture.loadFromFile("../resources/textures/dirt.png");



    sf::RenderWindow window(sf::VideoMode(1200, 800), "Anthill");

    sf::RectangleShape background(sf::Vector2f(1200, 800));
    background.setTexture(&background_texture);


    sf::RectangleShape storage(sf::Vector2f(200, 150)); // склад с едой
    storage.setTexture(&storage_texture);
    //storage_texture.setRepeated(true); // Включаем повторение текстуры
    //storage.setTextureRect(sf::IntRect(0, 0, 200, 150));
  // storage.setOutlineThickness(3.f);
   //storage.setOutlineColor(sf::Color(170, 170, 170));


    sf::RectangleShape trash(sf::Vector2f(200, 150)); // мусорка
    trash.setTexture(&trash_texture);
    /*/trash.setFillColor(sf::Color(64, 0, 0));
    trash.setOutlineThickness(5.f);
    trash.setOutlineColor(sf::Color(106, 0, 0));/*/


    sf::RectangleShape spawn_of_ants(sf::Vector2f(400, 75)); //спавн
    spawn_of_ants.setTexture(&ant_spawn_texture);
    /*/spawn_of_ants.setFillColor(sf::Color(0, 51, 25));
    spawn_of_ants.setOutlineThickness(4.f);
    spawn_of_ants.setOutlineColor(sf::Color(0, 120, 50));/*/

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
    Ant ant(0, 800);
    DrawableEntity *ant_render = new AntRender(ant, ant_texture);
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
