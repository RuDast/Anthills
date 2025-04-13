#include "TextureManager.h"
#include <stdexcept>

TextureManager& TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}

void TextureManager::loadTexture(const std::string& name, const std::string& path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        throw std::runtime_error("Failed to load texture: " + path);
    }
    textures[name] = std::move(texture);
}

sf::Texture& TextureManager::getTexture(const std::string& name) {
    return textures.at(name);
}