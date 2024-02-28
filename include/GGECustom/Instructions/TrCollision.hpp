#pragma once

#include "GGE/Instructions/Trigger.hpp"
#include "GGECustom/Pipes/PipesManager.hpp"
#include "GGE/Gobjects/KinematicBody.hpp"

namespace gge::ins {

// Some random trigger
class TrCollision : public Trigger
{
private:

public:
    std::weak_ptr<PipesManager> pipesManagerWeak;
    std::weak_ptr<obj::KinematicBody> bodyWeak;

    // Structors
    TrCollision();
    ~TrCollision();

    // Methods
    // checks for body-pipe / body-window border collision
    void checkEvent();
};

}
