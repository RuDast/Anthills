#include "AntRender.h"
#include <cmath>
#include <iostream>
#include "TextureManager.h"
#include "../models/Ant.h"
#include "../models/Roles/CleanerRole.h"
#include "../models/Roles/CollectorRole.h"
#include "../models/Roles/SoliderRole.h"

AntRender::AntRender(const Ant &ref) : ant_(ref) {
    sprite_.setTexture(TextureManager::getInstance().getTexture("common_ant"));
}

bool AntRender::isAlive() {
    return ant_.isAlive();
}

void AntRender::draw(sf::RenderWindow &window) {
    const float x = ant_.getX();
    const float y = ant_.getY();
    const float target_x = ant_.getTargetX();
    const float target_y = ant_.getTargetY();

    const float angle = atan2(target_y - y, target_x - x) * 180 / std::numbers::pi;

    sprite_.setRotation(angle - 90);
    sprite_.setPosition(x, y);
    window.draw(sprite_);
}

void AntRender::on_change_role(const Ant &ant) {
    if (const Role *ant_role = ant.getRole(); ant_role == Soldier)
        sprite_.setTexture(TextureManager::getInstance().getTexture("solider_ant"));
    else if (ant_role == Collector)
        sprite_.setTexture(TextureManager::getInstance().getTexture("collector_ant"));
    else if (ant_role == Cleaner)
        sprite_.setTexture(TextureManager::getInstance().getTexture("cleaner_ant"));
}

AntRender::~AntRender() {
    std::cout << "AntRender Destructor" << std::endl;
}
