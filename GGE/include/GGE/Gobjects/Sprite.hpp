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
    sf::Sprite sprite;

    // Structors
    Sprite();
    ~Sprite();

    // Methods
    // Set a texture
    void setTexture(const sf::Texture& texture);
    // draw self sprite
    void drawSelf(sf::RenderWindow& window);
    // set the flip of the object
    void setFlip(bool flip);
};

}