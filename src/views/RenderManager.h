#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
#include <vector>
#include "DrawableEntity.h"


class RenderManager {
public:
    RenderManager();

private:
    std::vector<DrawableEntity*> entities;

public:
    void addDrawable(DrawableEntity *entity);
    void drawAll(sf::RenderWindow& window);
};


#endif //RENDERMANAGER_H
