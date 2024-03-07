#include "GGE/Gobjects/KinematicBody.hpp"
#include "GGE/MathHelper.hpp"

using gge::obj::KinematicBody;

// Structors
KinematicBody::KinematicBody(){
    applyGravity = false;
    applyFriction = false;
    applyCollisions = false;
    applyControl = false;
    maxVelocity = -1;

    collisionDir = {Direction::None, Direction::None};
}
KinematicBody::~KinematicBody(){}

// Methods
// Control the body
void KinematicBody::control(){}

// set velocity
void KinematicBody::setVelocity(const sf::Vector2f& velocity){
    // Limit velocity if maxVelocity > 0
    this->velocity = maxVelocity < 0 ? velocity : clamp(velocity, -maxVelocity, maxVelocity);
}
// add velocity
void KinematicBody::addVelocity(const sf::Vector2f& velocity){
    setVelocity(getVelocity() + velocity);
}

// acceleration = acceleration
void KinematicBody::setAcceleration(const sf::Vector2f& acceleration){
    this->acceleration = acceleration;
}
// acceleration += acceleration
void KinematicBody::addAcceleration(const sf::Vector2f& acceleration){
    setAcceleration(this->acceleration + acceleration);
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
// applyGravity
bool KinematicBody::doApplyGravity(){
    return applyGravity;
}
// applyFriction
bool KinematicBody::doApplyFriction(){
    return applyFriction;
}
// applyControl
bool KinematicBody::doApplyControl(){
    return applyControl;
}

// velocity
const sf::Vector2f& KinematicBody::getVelocity(){
    return velocity;
}
// acceleration
const sf::Vector2f& KinematicBody::getAcceleration(){
    return acceleration;
}

// currentRect
const sf::FloatRect& KinematicBody::getCurrentRect(){
    return currentRect;
}
// previousRect
const sf::FloatRect& KinematicBody::getPreviousRect(){
    return previousRect;
}