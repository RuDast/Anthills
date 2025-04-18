#include "AntRender.h"
#include <cmath>
#include <iostream>
#include "TextureManager.h"
#include "../models/Ant.h"
#include "../models/Roles/CleanerRole.h"
#include "../models/Roles/CollectorRole.h"
#include "../models/Roles/NannyRole.h"
#include "../models/Roles/SoliderRole.h"

AntRender::AntRender(const Ant &ref) : ant_(ref)
{
    sprite_.setTexture(TextureManager::getInstance().getTexture("baby_ant"));
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

    const float angle = atan2(target_y - y, target_x - x) * 180 / 3.1415;

    sprite_.setRotation(angle - 90);
    sprite_.setPosition(x, y);
    window.draw(sprite_);
}

void AntRender::on_change_role(const Ant &ant)
{
    if (ant_.isAlive())
    {
        if (const Role *ant_role = ant.getRole(); ant_role == Nanny)
            sprite_.setTexture(TextureManager::getInstance().getTexture("nanny_ant"));
        else if (const Role *ant_role = ant.getRole(); ant_role == Soldier)
            sprite_.setTexture(TextureManager::getInstance().getTexture("solider_ant"));
        else if (ant_role == Collector)
            sprite_.setTexture(TextureManager::getInstance().getTexture("collector_ant"));
        else if (ant_role == Cleaner)
            sprite_.setTexture(TextureManager::getInstance().getTexture("cleaner_ant"));
    }
    else
    {
        if (const Role *ant_role = ant.getRole(); ant_role == Nanny)
            sprite_.setTexture(TextureManager::getInstance().getTexture("dnanny_ant"));
        else if (const Role *ant_role = ant.getRole(); ant_role == Soldier)
            sprite_.setTexture(TextureManager::getInstance().getTexture("dsolider_ant"));
        else if (ant_role == Collector)
            sprite_.setTexture(TextureManager::getInstance().getTexture("dcollector_ant"));
        else if (ant_role == Cleaner)
            sprite_.setTexture(TextureManager::getInstance().getTexture("dcleaner_ant"));
    }
}




AntRender::~AntRender()
{

}
