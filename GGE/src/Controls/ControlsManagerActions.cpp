#include "GGE/Controls/ControlsManager.hpp"
#include <iostream>

using gge::ControlsManager;

// makes everyControl.buffered = false (if not pressed right this frame)
void ControlsManager::clearStepBuffer(){
    // keyboard
    for(std::pair<const sf::Keyboard::Key, ControlParameters>& pair : activeControls.keyboard){
        pair.second.stepBuffered = pair.second.pressedNow;
    }
    
    // mouse
    for(std::pair<const sf::Mouse::Button, ControlParameters>& pair : activeControls.mouse){
        pair.second.stepBuffered = pair.second.pressedNow;
    }
}

// Set all the buffer controls state to past
void ControlsManager::update(){
    // keyboard
    for(auto it = activeControls.keyboard.begin(); it != activeControls.keyboard.end();){
        ControlParameters& params = it->second;
        params.pressedNow = false;

        if(params.held == false && params.stepBuffered == false){
            it = activeControls.keyboard.erase(it);
            continue;
        }

        ++it;
    }
    
    // mouse
    for(auto it = activeControls.mouse.begin(); it != activeControls.mouse.end();){
        ControlParameters& params = it->second;
        params.pressedNow = false;

        if(params.held == false && params.stepBuffered == false){
            it = activeControls.mouse.erase(it);
            continue;
        }

        ++it;
    }
}

// On control press
// keyboard
void ControlsManager::controlPress(sf::Keyboard::Key key){
    activeControls.keyboard[key] = {true, true, true};
}
// mouse
void ControlsManager::controlPress(sf::Mouse::Button button){
    activeControls.mouse[button] = {true, true, true};
}

// On control release
// keyboard
void ControlsManager::controlRelease(sf::Keyboard::Key key){
    if(!activeControls.keyboard.count(key)){
        return;
    }
    
    ControlParameters& params = activeControls.keyboard.at(key);
    params.held = false;
}
// mouse
void ControlsManager::controlRelease(sf::Mouse::Button button){
    if(!activeControls.mouse.count(button)){
        return;
    }
    
    ControlParameters& params = activeControls.mouse.at(button);
    params.held = false;
}