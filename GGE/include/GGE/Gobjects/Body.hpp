#pragma once

#include "Gobject.hpp"

namespace gge::obj {

class Body : public Gobject
{
protected:
    bool applyCollisions;

public:
    // Structors
    Body();
    ~Body();

    // Getters
    // collidable
    const bool& doApplyCollisions();
};

}
