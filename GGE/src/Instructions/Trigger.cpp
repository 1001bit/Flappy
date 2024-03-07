#include "GGE/Instructions/Trigger.hpp"

using gge::ins::Trigger;

// Structors
Trigger::Trigger(){
    active = true;
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
    actionsWeak.push_back(action);
}

// activate all the actions
void Trigger::activateActions(){
    for (auto it = actionsWeak.begin(); it != actionsWeak.end();){
        auto action = it->lock();
        if(!action){
            it = actionsWeak.erase(it);
            continue;
        }

        action->activate();

        ++it;
    }
}

// acitve
void Trigger::setActive(bool active){
    this->active = active;
}