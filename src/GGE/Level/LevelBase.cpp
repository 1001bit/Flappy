#include "GGE/Level.hpp"

using gge::Level;

// Structors
Level::Level(){}
Level::~Level(){
    // clear singleton managers on level delete
    ResourceManager* resourceManager = ResourceManager::getInstance();
    CooldownsManager* cooldownsManager = CooldownsManager::getInstance();
    resourceManager->clear();
    cooldownsManager->clear();
}