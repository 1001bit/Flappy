#pragma once

#include "Drawable.hpp"

namespace gge::obj {

class Sprite : public Drawable
{
private:
    // Methods
    // Update sprite and gobject pos
    void updatePos(); 

public:
    static const float SPRITE_SCALE;
    sf::Sprite sprite;

    // Structors
    Sprite();
    ~Sprite();

    // Methods
    // Set a texture
    void setTexture(const sf::Texture& texture);
    // draw self sprite
    void drawSelf(sf::RenderWindow& window);
    // set the flip of the object and sprite
    void setFlip(bool flip);
    // set the origin of the sprite
    void setOrigin(sf::Vector2f origin);
};

}