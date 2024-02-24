#include "GGE/Gobjects/KinematicBody.hpp"

using gge::obj::KinematicBody;

// Structors
KinematicBody::KinematicBody(){
    this->weighs = false;
    this->friction = false;
    this->collidable = false;

    this->collisionDir = {Direction::None, Direction::None};

    this->firstCurrentPosSet = true;
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

// Set current rect position
void KinematicBody::setCurrentPos(const sf::Vector2f& newPosition){
    currentRect.left = newPosition.x;
    currentRect.top = newPosition.y;

    // if called for the first time (on creation, for example), set same previousRect position to prevent glitchy behaviour
    if(firstCurrentPosSet){
        setRelativePos(newPosition);
        previousRect.left = newPosition.x;
        previousRect.top = newPosition.y;
        firstCurrentPosSet = false;
    }
}

// Move the current rect
void KinematicBody::moveCurrentRect(const sf::Vector2f& moveDistance){
    setCurrentPos(currentRect.getPosition() + moveDistance);
}

// set size of current rect
void KinematicBody::setRectSize(const sf::Vector2f& newSize){
    currentRect.width = newSize.x;
    currentRect.height = newSize.y;

    Gobject::setRectSize(newSize);
}

// set previousRect = currentRect
void KinematicBody::updatePreviousRect(){
    previousRect = currentRect;
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
// currentRect
const sf::FloatRect& KinematicBody::getCurrentRect(){
    return currentRect;
}
// previousRect
const sf::FloatRect& KinematicBody::getPreviousRect(){
    return previousRect;
}