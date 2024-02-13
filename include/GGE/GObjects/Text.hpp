#pragma once

#include "Drawable.hpp"

namespace gge::obj {

class Text : public Drawable
{
private:
    // Methods
    // Update text and gobject pos
    void updatePos(); 

public:
    // Structors
    Text();
    ~Text();

    // Variables
    sf::Text text;

    // Methods
    // draw self text
    void drawSelf(sf::RenderWindow& window);
};

}