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
        action->doAction();
    }
}

// set new action
void Trigger::setAction(std::shared_ptr<Action> newAction){
    action = newAction;
}