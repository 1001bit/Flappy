#include "GGE/Gobjects/KinematicBody.hpp"

using gge::obj::KinematicBody;

// Structors
KinematicBody::KinematicBody(){
    this->weighs = false;
    this->friction = false;
    this->collidable = false;
    this->collisionDir = {Direction::None, Direction::None};
}
KinematicBody::~KinematicBody(){}

// Methods
// Control the body
void KinematicBody::control(){}

// Accelerate the body
void KinematicBody::accelerate(float accelX, float accelY){
    acceleration.x += accelX;
    acceleration.y += accelY;
}

void KinematicBody::setCurrentPos(sf::Vector2f newPosition){
    currentRect.left = newPosition.x;
    currentRect.top = newPosition.y;
}

// Move the current rect
void KinematicBody::moveCurrentRect(sf::Vector2f moveDistance){
    setCurrentPos(currentRect.getPosition() + moveDistance);
}

// set size of current rect
void KinematicBody::setRectSize(const sf::Vector2f& newSize){
    currentRect.width = newSize.x;
    currentRect.height = newSize.y;

    Gobject::setRectSize(newSize);
}

// Getters
// weighs
const bool& KinematicBody::doesWeigh(){
    return weighs;
}
// friction
const bool& KinematicBody::doesFriction(){
    return friction;
}