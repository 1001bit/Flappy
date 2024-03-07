#include "Instructions/TrRestart.hpp"
#include "GGE/Controls/ControlsManager.hpp"

using gge::ins::TrRestart;

// Structors
TrRestart::TrRestart(std::shared_ptr<obj::Bird> bird) :
birdWeak(bird)
{}
TrRestart::~TrRestart(){}

// Methods
// checks if restart condition has happened
void TrRestart::checkEvent(){
    if(!active){
        return;
    }

    auto bird = birdWeak.lock();
    if(!bird){
        return;
    }

    ControlsManager* controlsManager = ControlsManager::getInstance();
    // if jumped and bird went some way down
    if(controlsManager->isPressed("jump") && bird->getCurrentRect().top > 1000){
        activateActions();
    }
}