#include "GGE/Level/LevelsManager.hpp"

using gge::LevelsManager;

// Update current level
void LevelsManager::updateCurrentLevel(const float& dTimeMs, sf::RenderWindow& window){
    auto currentLevel = currentLevelWeak.lock();
    if(!currentLevel){
        return;
    }

    // if level asks for reload - reload
    if(currentLevel->doRestart()){
        restartCurrentLevel();
        return;
    }

    // Cooldowns
    currentLevel->cooldownsManager.updateCooldowns(dTimeMs);
    if(currentLevel->isActive()){
        // Physics
        currentLevel->physicsManager.updateAll(dTimeMs);
        // All the Gobjects
        currentLevel->update(dTimeMs);
    }   
    // Instructions
    currentLevel->instructionsManager.update();

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