#include "GGE/Level/LevelsManager.hpp"

using gge::LevelsManager;

// Structors
LevelsManager::LevelsManager(){}
LevelsManager::~LevelsManager(){}

// Methods
// levelsMap[id] = level
void LevelsManager::makeLevel(ushort id, std::shared_ptr<Level> level){
    levelsMap[id] = level;
}

// levelsMap[id] = newLevel(func)
void LevelsManager::makeLevelByFunc(ushort id, plevelfunc levelFunc){
    std::shared_ptr<Level> level = std::make_shared<Level>();
    level->levelFunc = levelFunc;
    level = levelFunc();
    makeLevel(id, level);
}

// Load level from map by id
void LevelsManager::setCurrentLevel(ushort id){
    if(!levelsMap.count(id)){
        std::cout << "couldn't find any level with id " << id << "\n"; 
        return;
    }

    currentLevelWeak = levelsMap.at(id);
}

// Getters
// currentLevelWeak
std::weak_ptr<gge::Level> LevelsManager::getCurrentLevelWeak(){
    return currentLevelWeak;
}