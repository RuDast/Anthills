#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <string>
#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>


class TextureManager {
public:
    static TextureManager& getInstance();

    sf::Texture& getTexture(const std::string& name);
    void loadTexture(const std::string& name, const std::string& path);

private:
    TextureManager() = default;
    std::unordered_map<std::string, sf::Texture> textures;
};



#endif //TEXTUREMANAGER_H
