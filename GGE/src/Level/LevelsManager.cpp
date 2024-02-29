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

// levelsFuncMap[id] = levelsFuncMap
void LevelsManager::makeLevelFunc(ushort id, plevelfunc levelFunc){
    levelFuncsMap[id] = levelFunc;
}

// levelsMap[levelId] = levelsFuncMap[funcId]
void LevelsManager::makeLevelByFunc(ushort levelId, ushort funcId){
    if(!levelFuncsMap.count(funcId)){
        return;
    }

    levelsMap[levelId] = levelFuncsMap.at(funcId)();
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