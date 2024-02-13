#pragma once

#include <vector>
#include "GGE/Instructions/Trigger.hpp"

namespace gge {

class TriggersManager
{
private:
    std::vector<std::shared_ptr<ins::Trigger>> triggersVector;

public:
    // Structors
    TriggersManager();
    ~TriggersManager();

    // Methods
    // Check all the triggers if their event has happened
    void update();
    // Add new trigger
    void addNewTrigger(std::shared_ptr<ins::Trigger> newTrigger);
};

}