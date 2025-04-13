#include "RenderManager.h"

RenderManager::RenderManager() {
}

void RenderManager::addDrawable(DrawableEntity *entity) {
    entities.push_back(entity);
}

void RenderManager::drawAll(sf::RenderWindow& window) {
    for (auto item = entities.begin(); item != entities.end(); ) {
        if (!(*item)->isAlive()) {
            delete *item;
            item = entities.erase(item);
        } else {
            (*item)->draw(window);
            ++item;
        }
    }
}
