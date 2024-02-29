#pragma once

#include "Gobject.hpp"

namespace gge::obj {

class Body : public Gobject
{
protected:
    bool collidable;

public:
    // Structors
    Body();
    ~Body();

    // Getters
    // collidable
    const bool& isCollidable();
};

}
