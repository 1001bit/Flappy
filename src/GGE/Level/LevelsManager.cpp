#include "GGE/Level/LevelsManager.hpp"

using gge::LevelsManager;

// Structors
LevelsManager::LevelsManager(){}
LevelsManager::~LevelsManager(){}

// Methods
// Set map level
void LevelsManager::setNewMapLevel(ushort id, std::shared_ptr<Level> level){
    levelsMap[id] = level;
}

// Load level from map by id
void LevelsManager::setCurrentLevel(ushort id){
    if(!levelsMap.count(id)){
        return;
    }
    currentLevelWeak = levelsMap.at(id);
}

// Getters
// currentLevelWeak
std::weak_ptr<gge::Level> LevelsManager::getCurrentLevelWeak(){
    return currentLevelWeak;
}