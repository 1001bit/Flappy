#include "GGE/CustomGObjects/TDPlayer.hpp"

using gge::obj::TDPlayer;

constexpr float WALK_SPEED = 15;

// Structors
TDPlayer::TDPlayer(){
    this->weighs = 0;
    this->collidable = 1;
}

TDPlayer::~TDPlayer(){}

// Methods
// control
void TDPlayer::control(){
    gge::ControlsManager* controlsManager = gge::ControlsManager::getInstance();

    // walk left
    if(controlsManager->isControlHeld("wLeft")){
        accelerate(-WALK_SPEED, 0);
    }
    // walk right
    if(controlsManager->isControlHeld("wRight")){
        accelerate(WALK_SPEED, 0);
    }
    // walk up
    if(controlsManager->isControlHeld("wUp")){
        accelerate(0, -WALK_SPEED);
    }
    // walk down
    if(controlsManager->isControlHeld("wDown")){
        accelerate(0, WALK_SPEED);
    }
}