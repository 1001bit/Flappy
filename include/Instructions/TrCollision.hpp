#pragma once

#include "GGE/Instructions/Trigger.hpp"
#include "Pipes/PipesManager.hpp"
#include "GGE/Gobjects/KinematicBody.hpp"

namespace gge::ins {

// Some random trigger
class TrCollision : public Trigger
{
private:
    std::weak_ptr<PipesManager> pipesManagerWeak;
    std::weak_ptr<obj::KinematicBody> bodyWeak;
    std::weak_ptr<Level> levelWeak;

public:
    // Structors
    TrCollision(std::shared_ptr<PipesManager> pipesManager, std::shared_ptr<obj::KinematicBody> body, std::shared_ptr<Level> level);
    ~TrCollision();

    // Methods
    // checks for body-pipe / body-window border collision
    void checkEvent();
};

}
