#include "GGECustom/Gobjects/Bird.hpp"

using gge::obj::Bird;

constexpr float JUMP_FORCE = 9;

// Structors
Bird::Bird(){
    this->weighs = true;
    this->collidable = true;
}

Bird::~Bird(){}

// Methods
// control the player
void Bird::control(){
    gge::ControlsManager* controlsManager = gge::ControlsManager::getInstance();

    // jump
    if(controlsManager->isControlPressed("jump", 0)){
        velocity.y = 0;
        accelerate(0, -JUMP_FORCE);
    }
}