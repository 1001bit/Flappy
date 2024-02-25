#pragma once

#include <SFML/Graphics.hpp>

namespace gge {

class ResourceManager
{
private:
    // Storages
    // textures
    sf::Texture nullTexture;
    std::unordered_map<std::string, sf::Texture> textureCache;
    // fonts
    sf::Font nullFont;
    std::unordered_map<std::string, sf::Font> fontCache;

public: 
    // Structors
    ResourceManager();
    ~ResourceManager();

    // Get resource
    // Texture
    sf::Texture& getTexture(const std::string& path);
    // Font
    sf::Font& getFont(const std::string& path);
};

}