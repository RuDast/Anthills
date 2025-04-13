#include "AntRender.h"

#include <cmath>
#include <iostream>

<<<<<<< HEAD
AntRender::AntRender(const Ant &ref, const sf::Texture &texture) : ant_(ref)
{
    sprite_.setTexture(texture);
=======
#include "TextureManager.h"

AntRender::AntRender(const Ant &ref) : ant_(ref) {
    sprite_.setTexture(TextureManager::getInstance().getTexture("common_ant"));
>>>>>>> origin/roles
}

bool AntRender::isAlive()
{
    return ant_.isAlive();
}

void AntRender::draw(sf::RenderWindow &window)
{
    const float x = ant_.getX();
    const float y = ant_.getY();
    const float target_x = ant_.getTargetX();
    const float target_y = ant_.getTargetY();

    float angle = atan2(target_y - y, target_x - x) * 180 / std::numbers::pi;

    sprite_.setRotation(angle - 90);
    sprite_.setPosition(x, y);
    window.draw(sprite_);
}

void AntRender::on_change_role(const Ant &ant)
{
    std::cout << "Sprite changed" << std::endl;
}

AntRender::~AntRender()
{
    std::cout << "AntRender Destructor" << std::endl;
}
