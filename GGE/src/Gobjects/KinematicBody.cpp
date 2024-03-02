#include "GGE/Gobjects/KinematicBody.hpp"

using gge::obj::KinematicBody;

// Structors
KinematicBody::KinematicBody(){
    weighs = false;
    friction = false;
    collidable = false;
    collisionDir = {Direction::None, Direction::None};
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
void KinematicBody::setCurrentPos(const sf::Vector2f& pos, bool teleport){
    currentRect.left = pos.x;
    currentRect.top = pos.y;

    // if teleport, set the same previousRect and selfRect position to prevent glitchy behaviour
    if(teleport){
        setRelativePos(pos);
        previousRect.left = pos.x;
        previousRect.top = pos.y;
    }
}

// Move the current rect
void KinematicBody::moveCurrentRect(const sf::Vector2f& moveDistance){
    setCurrentPos(currentRect.getPosition() + moveDistance);
}

// set size of current rect
void KinematicBody::setRectSize(const sf::Vector2f& size){
    currentRect.width = size.x;
    currentRect.height = size.y;

    Gobject::setRectSize(size);
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