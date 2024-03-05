#include "GGE/Gobjects/AnimatedSprite.hpp"

using gge::obj::AnimatedSprite;

// Structors
AnimatedSprite::AnimatedSprite() {
    elapsedTime = 0;
    currentAnimation = nullptr;
}

AnimatedSprite::~AnimatedSprite(){};

// Methods
// add animation to animation map
void AnimatedSprite::insertAnimation(std::string name, const Animation& animation){
    animationMap.insert({name, animation});
}

// start animation
void AnimatedSprite::playAnimation(std::string name){
    // if no animation with such name
    if(!animationMap.count(name)){
        return;
    }

    // if some animation is playing right now
    if(currentAnimation != nullptr){
        // can't play same animation as current
        if(currentAnimation == &animationMap.at(name)){
            return;
        }
        // if current animation is not looped - stop
        if(!currentAnimation->looped){
            return;
        }
    }

    // start new animation
    elapsedTime = 0;
    currentAnimation = &animationMap.at(name);    
    update(0);
    setTexture(*(currentAnimation->texture));
}

// update frames, etc
void AnimatedSprite::update(const float& dTimeMs){
    // stop if no current animation
    if(currentAnimation == nullptr){
        return;
    }

    // set rect of current frame of current animation
    sprite.setTextureRect(getCurrentFrame());
    
    // restart animation or stop animation if elapsedTime is more that animation time
    elapsedTime += dTimeMs;
    if(elapsedTime >= currentAnimation->playTime){
        elapsedTime -= currentAnimation->playTime;
        if(!currentAnimation->looped){
            currentAnimation = nullptr;
        }
    }
}


// Getters
// returns current frame rect
const sf::IntRect& AnimatedSprite::getCurrentFrame(){
    if(currentAnimation->playTime == 0){
        return currentAnimation->frames[0];
    }
    return currentAnimation->frames[elapsedTime/currentAnimation->frameTime];
}