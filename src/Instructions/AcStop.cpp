#include "Instructions/AcStop.hpp"

using gge::ins::AcStop;

// Structors
AcStop::AcStop(std::shared_ptr<obj::Bird> bird, std::shared_ptr<PipesManager> pipesManager,
std::shared_ptr<BackgroundManager> backgroundManager, std::shared_ptr<TrRestart> restartTrigger) :
birdWeak(bird),
pipesManagerWeak(pipesManager),
backgroundManagerWeak(backgroundManager),
restartTriggerWeak(restartTrigger)
{}
AcStop::~AcStop(){}

// Methods
// stop bird, backgrounds manager and pipes manager
void AcStop::activate(){
    auto backgroundManager = backgroundManagerWeak.lock();
    auto bird = birdWeak.lock();
    auto pipesManager = pipesManagerWeak.lock();
    auto restartTrigger = restartTriggerWeak.lock();
    if(!backgroundManager || !bird || !pipesManager || !restartTrigger){
        return;
    }

    backgroundManager->stop();
    pipesManager->stop();
    bird->kill();
    restartTrigger->setActive(true);
}