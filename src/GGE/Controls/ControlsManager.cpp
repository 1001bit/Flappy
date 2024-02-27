#include "GGE/Controls/ControlsManager.hpp"

using gge::ControlsManager;

// Singleton
ControlsManager* ControlsManager::instance = nullptr;
ControlsManager* ControlsManager::getInstance(){
    if (!instance)
        instance = new ControlsManager();
    return instance;
}

// Methods
// Set Controls map
void ControlsManager::setKeyboardControlsMap(std::unordered_map<std::string, sf::Keyboard::Key> newControlsMap){
    keyboardControlsMap = newControlsMap;
}

void ControlsManager::setMouseControlsMap(std::unordered_map<std::string, sf::Mouse::Button> newControlsMap){
    mouseControlsMap = newControlsMap;
};

// Check if held
bool ControlsManager::isHeld(const std::string& controlId){
    // if there is such keyboard control and it's pressed
    if(keyboardControlsMap.count(controlId)){
        if(heldKeyboardKeys.count(keyboardControlsMap.at(controlId))){
            return 1;
        }
    }
    // if there is such mouse control and it's pressed
    else if(mouseControlsMap.count(controlId)){
        if(heldMouseButtons.count(mouseControlsMap.at(controlId))){
            return 1;
        }
    }
    return 0;
}

// check if pressed once
bool ControlsManager::isPressed(const std::string& controlId, bool isPressedNow){
    // if there is such keyboard control
    if(keyboardControlsMap.count(controlId)){
        sf::Keyboard::Key& key = keyboardControlsMap.at(controlId);
        // if it's pressed
        if(pressedKeyboardBuffer.count(key)){
            // check if it's pressed now or in past
            if(!pressedKeyboardBuffer.at(key) && isPressedNow){
                return 0;
            }

            return 1;
        }
    }

    // if there is such mouse control
    else if(mouseControlsMap.count(controlId)){
        sf::Mouse::Button& button = mouseControlsMap.at(controlId);
        // if it's pressed
        if(pressedMouseBuffer.count(button)){
            // check if it's pressed now or in past
            if(!pressedMouseBuffer.at(button) && isPressedNow){
                return 0;
            }

            return 1;
        }
    }

    return 0;
}

// Change control
void ControlsManager::changeKeyboardControl(std::string controlId, sf::Keyboard::Key newKey){
    if(!keyboardControlsMap.count(controlId)){
        return;
    }
    keyboardControlsMap.at(controlId) = newKey;
}

// On control press
void ControlsManager::controlPress(sf::Keyboard::Key key){
    pressedKeyboardBuffer[key] = true;
    heldKeyboardKeys.insert(key);
}

void ControlsManager::controlPress(sf::Mouse::Button button){
    pressedMouseBuffer[button] = 1;
    heldMouseButtons.insert(button);
}

// On control release
void ControlsManager::controlRelease(sf::Keyboard::Key key){
    heldKeyboardKeys.erase(key);
}

void ControlsManager::controlRelease(sf::Mouse::Button button){
    heldMouseButtons.erase(button);
}

// Clear the vectors of once pressed controls of controls, that were pressed in the past
void ControlsManager::clearPastBuffer(){
    // keyboard
    for(auto it = pressedKeyboardBuffer.begin(); it != pressedKeyboardBuffer.end();){
        if(!it->second){
            it = pressedKeyboardBuffer.erase(it);
            continue;
        }
        ++it;
    }

    // mouse
    for(auto it = pressedMouseBuffer.begin(); it != pressedMouseBuffer.end();){
        if(!it->second){
            it = pressedMouseBuffer.erase(it);
            continue;
        }
        ++it;
    }
}

// Set all the buffer controls state to past
void ControlsManager::updateBuffer(){
    // keyboard
    for(std::pair<const sf::Keyboard::Key, bool>& pair : pressedKeyboardBuffer){
        pair.second = false;
    }
    
    // mouse
    for(std::pair<const sf::Mouse::Button, bool>& pair : pressedMouseBuffer){
        pair.second = false;
    }
}