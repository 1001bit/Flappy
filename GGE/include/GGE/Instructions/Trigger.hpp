#pragma once

#include <memory>
#include <vector>
#include "GGE/Instructions/Action.hpp"

namespace gge::ins {

class Trigger
{
private:

protected:
    bool active;
    std::vector<std::weak_ptr<Action>> actionsWeak;

    // Methods
    // activate all the actions
    void activateActions();

public:
    // Structors
    Trigger();
    ~Trigger();

    // Methods
    // checks if event has happened and does action if yes
    virtual void checkEvent();
    // add an action to vector
    void addAction(std::shared_ptr<Action> action);
    // acitve
    void setActive(bool active);
};

}