#include "GGE/SingletonManagers/ControlsManager.hpp"

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

// check if held
bool ControlsManager::isControlPressed(const std::string& controlId){
    // if there is such keyboard control and it's pressed
    if(keyboardControlsMap.count(controlId)){
        if(pressedOnceKeyboardKeys.count(keyboardControlsMap.at(controlId))){
            return 1;
        }
    }
    // if the control wasn't pressed this frame
    else if(mouseControlsMap.count(controlId)){
        if(pressedOnceMouseButtons.count(mouseControlsMap.at(controlId))){
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
    pressedOnceKeyboardKeys.insert(key);
    heldKeyboardKeys.insert(key);
}

void ControlsManager::addPressedMouse(sf::Mouse::Button button){
    pressedOnceMouseButtons.insert(button);
    heldMouseButtons.insert(button);
}

// Clear pressed once
void ControlsManager::clearPressed(){
    pressedOnceKeyboardKeys.clear();
    pressedOnceMouseButtons.clear();
}

// Control release
void ControlsManager::keyboardControlRelease(sf::Keyboard::Key key){
    heldKeyboardKeys.erase(key);
}

void ControlsManager::mouseControlRelease(sf::Mouse::Button button){
    heldMouseButtons.erase(button);
}