#include "GGE/Gobjects/Animation.hpp"

// Structors

Animation::Animation(sf::Texture& texture, int frameWidth, float playTime, bool looped) :
texture(&texture),
playTime(playTime),
looped(looped)
{
    // add frames to vector depending on frame width
    for(int x = 0; x < int(this->texture->getSize().x / frameWidth); ++x){
        this->frames.push_back(sf::IntRect(x*frameWidth, 0, frameWidth, this->texture->getSize().y));
    }

    this->frameTime = this->playTime / this->frames.size();
}

Animation::Animation(){}