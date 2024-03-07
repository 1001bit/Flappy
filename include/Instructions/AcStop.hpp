#pragma once

#include "GGE/Instructions/Action.hpp"
#include "Gobjects/Bird.hpp"
#include "Background/BackgroundManager.hpp"
#include "Pipes/PipesManager.hpp"
#include "Instructions/TrRestart.hpp"

namespace gge::ins {

class AcStop : public gge::ins::Action
{
private:

std::weak_ptr<obj::Bird> birdWeak;
std::weak_ptr<PipesManager> pipesManagerWeak;
std::weak_ptr<BackgroundManager> backgroundManagerWeak;
std::weak_ptr<TrRestart> restartTriggerWeak;

public:
    // Structors
    AcStop(std::shared_ptr<obj::Bird> bird, std::shared_ptr<PipesManager> pipesManager, 
    std::shared_ptr<BackgroundManager> backgroundManager, std::shared_ptr<TrRestart> restartTrigger);
    ~AcStop();

    // Methods
    // stop bird, backgrounds manager and pipes manager
    void activate();
};

}