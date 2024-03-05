#include "GGE/Controls/ControlsManager.hpp"
#include <iostream>

using gge::ControlsManager;

// Check if held
bool ControlsManager::isHeld(const std::string& controlId){
    if(!controlsMap.count(controlId)){
        return false;
    }

    // keyboard
    for(sf::Keyboard::Key key : controlsMap.at(controlId).keyboard){
        if(activeControls.keyboard.count(key)){
            return activeControls.keyboard.at(key).held;
        }
    }
    // mouse
    for(sf::Mouse::Button button : controlsMap.at(controlId).mouse){
        if(activeControls.mouse.count(button)){
            return activeControls.mouse.at(button).held;
        }
    }

    return false;
}

// check if pressed once
bool ControlsManager::isPressed(const std::string& controlId, bool checkStepBuffer){
    if(!controlsMap.count(controlId)){
        return false;
    }

    // keyboard
    for(sf::Keyboard::Key key : controlsMap.at(controlId).keyboard){
        // if no such active control
        if(!activeControls.keyboard.count(key)){
            continue;
        }
        const ControlParameters& params = activeControls.keyboard.at(key);
        // if not in pressed buffer
        if(!params.stepBuffered){
            continue;
        }
        // if asked for only current, but is not current
        if(!checkStepBuffer && !params.pressedNow){
            continue;
        }

        return true;
    }

    // mouse
    for(sf::Mouse::Button button : controlsMap.at(controlId).mouse){
        // if no such active control
        if(!activeControls.mouse.count(button)){
            continue;
        }
        const ControlParameters& params = activeControls.mouse.at(button);
        // if not in pressed buffer
        if(!params.stepBuffered){
            continue;
        }
        // if asked for only current, but is not current
        if(!checkStepBuffer && !params.pressedNow){
            continue;
        }

        return true;
    }

    return false;
}