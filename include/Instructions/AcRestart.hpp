#pragma once

#include "GGE/Instructions/Action.hpp"
#include "GGE/Level/Level.hpp"

class AcRestart : public gge::ins::Action
{
private:
    
public:
    // Structors
    AcRestart();
    ~AcRestart();

    // Methods
    // wait 3 seconds and restart the level
    void activate();
};