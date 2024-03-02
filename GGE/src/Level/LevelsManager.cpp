#include "GGE/Level/LevelsManager.hpp"

using gge::LevelsManager;

// Structors
LevelsManager::LevelsManager(){}
LevelsManager::~LevelsManager(){}

// Methods
// update current level
void LevelsManager::updateCurrentLevel(const float& dTimeMs, sf::RenderWindow& window){
    auto currentLevel = currentLevelWeak.lock();
    if(!currentLevel){
        return;
    }

    // if level asks for reload - reload
    if(currentLevel->restart){
        restartCurrentLevel();
        return;
    }

    // Cooldowns
    currentLevel->cooldownsManager.updateCooldowns(dTimeMs);

    // Physics
    currentLevel->physicsManager.updateAll(dTimeMs);

    // Triggers
    currentLevel->instructionsManager.update();

    // Gobjects that are level's children
    currentLevel->update(dTimeMs);

    // Draw
    window.clear();
    
    auto levelView = currentLevel->levelViewWeak.lock();
    auto guiView = currentLevel->guiViewWeak.lock();
    if(levelView && guiView){
        currentLevel->drawablesManager.draw(window, levelView, guiView);
    }

    #ifdef DRAW_COLLIDERS
    currentLevel->physicsManager.drawColliders(window, levelView);
    #endif

    window.display();
}

// levelsMap[id] = level
void LevelsManager::makeLevel(ushort id, std::shared_ptr<Level> level){
    levelsMap[id] = level;
}

// levelsMap[id] = newLevel(func)
void LevelsManager::makeLevelByFunc(ushort id, plevelfunc levelFunc){
    levelFuncsMap[id] = levelFunc;
    levelsMap[id] = levelFunc();
}

// Load level from map by id
void LevelsManager::setCurrentLevel(ushort id){
    if(!levelsMap.count(id)){
        std::cout << "couldn't find any level with id " << id << "\n"; 
        return;
    }

    currentLevelId = id;
    currentLevelWeak = levelsMap.at(id);
}

// restart current level with function or not
void LevelsManager::restartCurrentLevel(){
    if(levelFuncsMap.count(currentLevelId)){
        levelsMap.at(currentLevelId) = levelFuncsMap.at(currentLevelId)();
    } else {
        levelsMap.at(currentLevelId) = std::make_shared<Level>();
    }
    setCurrentLevel(currentLevelId);
}

// Getters
// currentLevelWeak
std::weak_ptr<gge::Level> LevelsManager::getCurrentLevelWeak(){
    return currentLevelWeak;
}