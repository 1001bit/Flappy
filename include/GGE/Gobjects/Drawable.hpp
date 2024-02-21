#pragma once

#include "Gobject.hpp"

namespace gge::obj {

class Drawable : public Gobject
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