#pragma once

#include "GGE/GObjects/GObject.hpp"
#include "GGE/Instructions/Action.hpp"

namespace gge::ins {

class Trigger
{
private:

protected:
    // Variables
    bool active;
    std::shared_ptr<Action> action;

public:
    // Structors
    Trigger();
    ~Trigger();

    // Methods
    // checks if event has happened and does action if yes
    virtual void checkEvent();
    // set new action
    void setAction(std::shared_ptr<Action> newAction);
};

}