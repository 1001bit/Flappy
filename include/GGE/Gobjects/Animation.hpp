#pragma once

#include <SFML/Graphics.hpp>

struct Animation
{
    sf::Texture* texture;
    std::vector<sf::IntRect> frames;
    float playTime;
    float frameTime;
    bool isLooped;
    
    // Structors
    Animation(sf::Texture& newTexture, int frameWidth, float playTime, bool isLooped);
    Animation();
};