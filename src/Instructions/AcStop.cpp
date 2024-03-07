#include "Instructions/AcStop.hpp"

using gge::ins::AcStop;

// Structors
AcStop::AcStop(std::shared_ptr<obj::Bird> bird, std::shared_ptr<PipesManager> pipesManager, std::shared_ptr<BackgroundManager> backgroundManager) :
birdWeak(bird),
pipesManagerWeak(pipesManager),
backgroundManagerWeak(backgroundManager)
{}
AcStop::~AcStop(){}

// Methods
// stop bird, backgrounds manager and pipes manager
void AcStop::activate(){
    auto backgroundManager = backgroundManagerWeak.lock();
    auto bird = birdWeak.lock();
    auto pipesManager = pipesManagerWeak.lock();
    if(!backgroundManager || !bird || !pipesManager){
        return;
    }

    backgroundManager->stop();
    pipesManager->stop();
    bird->kill();
}