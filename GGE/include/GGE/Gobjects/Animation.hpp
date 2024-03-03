#pragma once

#include <SFML/Graphics.hpp>

struct Animation
{
    sf::Texture* texture;
    std::vector<sf::IntRect> frames;
    float playTime;
    float frameTime;
    bool looped;
    
    // Structors
    Animation(sf::Texture& texture, int frameWidth, float playTime, bool looped);
    Animation();
};