#include "GGE/GObjects/Animation.hpp"

// Structors

Animation::Animation(sf::Texture& newTexture, int frameWidth, float playTime, bool isLooped){
    texture = &newTexture;

    // add frames to vector depending on frame width
    for(int x = 0; x < int(texture->getSize().x / frameWidth); ++x){
        this->frames.push_back(sf::IntRect(x*frameWidth, 0, frameWidth, texture->getSize().y));
    }

    this->playTime = playTime;
    this->frameTime = this->playTime / this->frames.size();
    this->isLooped = isLooped;
}

Animation::Animation(){}