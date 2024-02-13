#include "GGE/CustomGObjects/TDNpc.hpp"

using gge::obj::TDNpc;

constexpr float WALK_SPEED = 4;
constexpr unsigned MOVEMENT_RAND = 500;

// Structors
TDNpc::TDNpc(){
    this->movementDir = Direction::None;

    this->weighs = 0;
    this->collidable = 1;
    
    gge::CooldownsManager* cooldownsManager = gge::CooldownsManager::getInstance();
    selfCooldownMap["idle"] = cooldownsManager->newCooldown(gge::Cooldown(2000));
    selfCooldownMap["walk"] = cooldownsManager->newCooldown(gge::Cooldown(3000));
}
TDNpc::~TDNpc(){}

// Methods
// npc movement
void TDNpc::control(){
    // no movement while on idle cooldown
    if(selfCooldownMap.at("idle")->getCurrentValueMs()){
        return;
    }

    // if movement cooldown is over - start idle
    if((!selfCooldownMap.at("walk")->getCurrentValueMs() && movementDir != Direction::None)){
        movementDir = Direction::None;
        selfCooldownMap.at("idle")->start(MOVEMENT_RAND);
        return;
    }

    // if collision and walking in collision direction - start idle and stop walk
    if(selfCooldownMap.at("walk")->getCurrentValueMs() && movementDir == collisionDir.horizontal){
        movementDir = Direction::None;
        selfCooldownMap.at("walk")->stop();
        selfCooldownMap.at("idle")->start(MOVEMENT_RAND);
        return;
    }

    // if idle cooldown is over and movementDir is still none
    if(!selfCooldownMap.at("idle") && movementDir == Direction::None){
        movementDir = static_cast<Direction>(rand() % 4 + 1);
        selfCooldownMap.at("walk")->start(1000);
    }

    // movement depending on direction
    switch (movementDir)
    {
    case Direction::Up:
        accelerate(0, -WALK_SPEED);
        break;
    case Direction::Down:
        accelerate(0, WALK_SPEED);
        break;
    case Direction::Left:
        accelerate(-WALK_SPEED, 0);
        break;
    case Direction::Right:
        accelerate(WALK_SPEED, 0);
        break;
    default:
        break;
    }
}