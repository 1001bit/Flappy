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
    // Structors
    Sprite();
    ~Sprite();

    // Variables
    sf::Sprite sprite;

    // Methods
    // Set a texture
    void setTexture(const sf::Texture& newTexture);
    // draw self sprite
    void drawSelf(sf::RenderWindow& window);
    // set the flip of the object
    void setFlip(bool newFlip);
};

}