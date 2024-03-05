#include "GGE/Controls/ControlsManager.hpp"

using gge::ControlsManager;

// Singleton
ControlsManager* ControlsManager::instance = nullptr;
ControlsManager* ControlsManager::getInstance(){
    if (!instance)
        instance = new ControlsManager();
    return instance;
}

// Set Controls map
void ControlsManager::setControlsMap(std::unordered_map<std::string, Control> controlsMap){
    this->controlsMap = controlsMap;
}

// Change control
void ControlsManager::changeControl(const std::string& controlId, const Control& control){
    if(!controlsMap.count(controlId)){
        return;
    }
    controlsMap.at(controlId) = control;
}