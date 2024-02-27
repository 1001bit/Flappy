#pragma once

#include <vector>
#include "GGE/Instructions/Trigger.hpp"

namespace gge {

class InstructionsManager
{
private:

public:
    std::vector<std::shared_ptr<ins::Trigger>> triggersVector;
    std::vector<std::shared_ptr<ins::Action>> actionsVector;

    // Structors
    InstructionsManager();
    ~InstructionsManager();

    // Methods
    // Check all the triggers if their event has happened
    void update();
};

}