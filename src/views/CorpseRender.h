#ifndef CORPSERENDER_H
#define CORPSERENDER_H



// CorpseRender.h
#pragma once
#include "DrawableEntity.h"
#include "../models/Corpse.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

class CorpseRender : public DrawableEntity {
public:
    explicit CorpseRender(const Corpse& c)
      : corpse_(c)
    {
        sprite_.setTexture(TextureManager::getInstance().getTexture("corpse"));
        sprite_.setOrigin(
            sprite_.getTexture()->getSize().x  * 0.5f,
            sprite_.getTexture()->getSize().y  * 0.5f
        );
    }

    bool isAlive() override {
        // пока труп не доставлен на свалку, жив
        return corpse_.getState() != CorpseState::on_trash;
    }

    void draw(sf::RenderWindow& window) override {
        sprite_.setPosition(corpse_.getX(), corpse_.getY());
        window.draw(sprite_);
    }

private:
    const Corpse& corpse_;
    sf::Sprite    sprite_;
};




#endif //CORPSERENDER_H
