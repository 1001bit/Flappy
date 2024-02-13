#pragma once

#include "GGE/GObjects/KinematicBody.hpp"

namespace gge::obj {

class TDNpc : public KinematicBody
{
private:
    // Variables
    Direction movementDir;

public:
    // Structors
    TDNpc();
    ~TDNpc();

    // Methods
    // npc movement
    void control();
};

}