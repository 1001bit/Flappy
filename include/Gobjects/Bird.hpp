#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"
#include "GGE/Controls/ControlsManager.hpp"

namespace gge::obj {

class Bird : public KinematicBody
{
private:

public:
    // Structors
    Bird();
    ~Bird();

    // Methods
    // Control player
    void control();
};

}
