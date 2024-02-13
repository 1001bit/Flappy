#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Drawable.hpp"

typedef std::unordered_map<std::string, Animation> anim_map;

namespace gge::obj {

class AnimatedSprite : public Drawable {

private:
    // Variables
    anim_map animationMap;
    Animation* currentAnimation;
    float elapsedTime;

    // Methods
    // Update sprite and gobject pos
    void updatePos(); 

public:
    // Structors
    AnimatedSprite();
    ~AnimatedSprite();

    // Variables
    sf::Sprite sprite;

    // Methods
    // Start animation with name
    void playAnimation(std::string name);
    // Update the state of current animation
    void update(const float& dTimeMs);
    // draw self sprite
    void drawSelf(sf::RenderWindow& window);
    // Add new animation with name
    void insertAnimation(std::string name, const Animation& animation);

    // Getters
    // Get rect of current animation's frame
    const sf::IntRect& getCurrentFrame();
};

}