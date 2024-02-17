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
bool ControlsManager::isControlHeld(const std::string& controlId){
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
bool ControlsManager::isControlPressed(const std::string& controlId, bool isPressedNow){
    // if there is such keyboard control
    if(keyboardControlsMap.count(controlId)){
        sf::Keyboard::Key& key = keyboardControlsMap.at(controlId);
        // if it's pressed
        if(pressedKeyboardBuffer.count(key)){
            // check if it's pressed now or in past
            if(!pressedKeyboardBuffer.at(key) && isPressedNow){
                return 0;
            }

            pressedKeyboardBuffer.at(key) = 0;
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

            pressedMouseBuffer.at(button) = 0;
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

// Add pressed once
void ControlsManager::addPressedKeyboard(sf::Keyboard::Key key){
    pressedKeyboardBuffer[key] = 1;
    heldKeyboardKeys.insert(key);
}

void ControlsManager::addPressedMouse(sf::Mouse::Button button){
    pressedMouseBuffer[button] = 1;
    heldMouseButtons.insert(button);
}

// Clear the vectors of once pressed controls of controls, that were pressed in the past
void ControlsManager::clearPastBuffer(){
    for(auto it = pressedKeyboardBuffer.begin(); it != pressedKeyboardBuffer.end();){
        if(!it->second){
            it = pressedKeyboardBuffer.erase(it);
            continue;
        }
        ++it;
    }

    for(auto it = pressedMouseBuffer.begin(); it != pressedMouseBuffer.end();){
        if(!it->second){
            it = pressedMouseBuffer.erase(it);
            continue;
        }
        ++it;
    }
}

// Control release
void ControlsManager::keyboardControlRelease(sf::Keyboard::Key key){
    heldKeyboardKeys.erase(key);
}

void ControlsManager::mouseControlRelease(sf::Mouse::Button button){
    heldMouseButtons.erase(button);
}