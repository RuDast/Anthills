#include <iostream>
#include "TextureManager.h"
#include "enemy_render.h"

EnemyRender::EnemyRender(const Enemy& enemy): enemy_(enemy)
{
    sprite_.setTexture(TextureManager::getInstance().getTexture("enemy"));
}


void EnemyRender::draw(sf::RenderWindow &window)
{
    const float X = enemy_.getX();
    const float Y = enemy_.getY();

    sprite_.setPosition(X,Y);
    window.draw(sprite_);
}

bool EnemyRender::isAlive()
{
    return enemy_.getIsAlive();
}


EnemyRender::~EnemyRender()
{
    std::cout<< "EnemyRender Destructor"<<std::endl;
}


