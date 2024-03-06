#pragma once

#include "GGE/Instructions/Action.hpp"
#include "GGE/Level/Level.hpp"
#include "Pipes/PipesManager.hpp"

namespace gge::ins {

class AcRestart : public gge::ins::Action
{
private:

std::weak_ptr<Level> levelWeak;

public:
    // Structors
    AcRestart(std::shared_ptr<Level> level);
    ~AcRestart();

    // Methods
    // wait 3 seconds and restart the level
    void activate();
};

}