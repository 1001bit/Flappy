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
    sf::Text text;

    // Structors
    Text();
    ~Text();

    // Methods
    // draw self text
    void drawSelf(sf::RenderWindow& window);
};

}