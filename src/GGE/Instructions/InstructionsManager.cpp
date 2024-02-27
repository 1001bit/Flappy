#include "GGE/Instructions/InstructionsManager.hpp"

using gge::InstructionsManager;

// Structors
InstructionsManager::InstructionsManager(){}
InstructionsManager::~InstructionsManager(){}

// Methods
// Check all the triggers if their event has happened
void InstructionsManager::update(){
    for(auto trigger : triggersVector){
        trigger->checkEvent();
    }
}