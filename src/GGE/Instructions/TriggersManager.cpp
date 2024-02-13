#include "GGE/Instructions/TriggersManager.hpp"

using gge::TriggersManager;

// Structors
TriggersManager::TriggersManager(){}
TriggersManager::~TriggersManager(){}

// Methods
// Check all the triggers if their event has happened
void TriggersManager::update(){
    for(auto trigger : triggersVector){
        trigger->checkEvent();
    }
}

// Add new trigger
void TriggersManager::addNewTrigger(std::shared_ptr<gge::ins::Trigger> newTrigger){
    triggersVector.push_back(newTrigger);
}