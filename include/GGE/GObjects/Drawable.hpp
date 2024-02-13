#pragma once

#include "GObject.hpp"

namespace gge::obj {

class Drawable : public GObject
{
private:
    
public:
    // Structors
    Drawable();
    ~Drawable();

    // Methods
    // draw self drawable object
    virtual void drawSelf(sf::RenderWindow& window);
};

}