#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Sprite.hpp"

typedef std::unordered_map<std::string, Animation> anim_map;

namespace gge::obj {

class AnimatedSprite : public Sprite {

private:
    anim_map animationMap;
    Animation* currentAnimation;
    float elapsedTime;

public:
    // Structors
    AnimatedSprite();
    ~AnimatedSprite();

    // Methods
    // Start animation with name
    void playAnimation(std::string name);
    // Update the state of current animation
    void update(const float& dTimeMs);
    // Add new animation with name
    void insertAnimation(std::string name, const Animation& animation);

    // Getters
    // Get rect of current frame of the current animation
    const sf::IntRect& getCurrentFrame();
};

}