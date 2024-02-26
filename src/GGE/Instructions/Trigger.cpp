#include "GGE/Instructions/Trigger.hpp"

using gge::ins::Trigger;

// Structors
Trigger::Trigger(){
    active = 1;
}
Trigger::~Trigger(){}

// Methods
// checks if event has happened and does action if yes
void Trigger::checkEvent(){
    if(active){
        activateActions();
    }
}

// add an action
void Trigger::addAction(std::shared_ptr<Action> action){
    actions.push_back(action);
}

// activate all the actions
void Trigger::activateActions(){
    for (std::shared_ptr<Action> action : actions){
        action->doAction();
    }
}