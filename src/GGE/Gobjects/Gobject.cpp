#include "GGE/Gobjects/Gobject.hpp"

using gge::obj::Gobject;

// Structors
Gobject::Gobject(){
    this->flipped = false;
    this->doesFlipMirror = false;
}

Gobject::~Gobject(){
    // std::cout << "deleted\n";
}

// Methods
// Update the state of the object
void Gobject::update(const float& dTimeMs){}

// Set position relative to parent's position
void Gobject::setRelativePos(const sf::Vector2f& newRelativePos){
    relativePos = newRelativePos;
    updatePos();
}

// move self by some distance
void Gobject::move(const sf::Vector2f& distance){
    setRelativePos(getRelativePos() + distance);
}

// update everything related to position
void Gobject::updatePos(){
    sf::Vector2f zeroPoint;

    if(auto parent = parentWeak.lock()){
        zeroPoint.x = parent->getRect().left;
        zeroPoint.y = parent->getRect().top;
    }
    
    selfRect.left = zeroPoint.x + relativePos.x;
    selfRect.top = zeroPoint.y + relativePos.y;

    // update children's position
    for(std::shared_ptr<Gobject> child : children) {
        child->updatePos();
    }
}

// Add a new child
void Gobject::addChild(std::shared_ptr<Gobject> newChild){
    if(auto childOldParent = newChild->parentWeak.lock()){
        childOldParent->removeChild(newChild);
    }

    newChild->parentWeak = shared_from_this();
    children.push_back(newChild);
    newChild->updatePos();
}

// Remove existing child
void Gobject::removeChild(std::shared_ptr<Gobject> child){
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

// Destroy self
void Gobject::removeSelf(){
    if(auto parent = parentWeak.lock()){
        parent->removeChild(shared_from_this());
    }
}

// set size of selfRect
void Gobject::setRectSize(const sf::Vector2f& newSize){
    selfRect.width = newSize.x;
    selfRect.height = newSize.y;
}

// set size of selfRect in pixels
void Gobject::setRectPixelSize(float w, float h){
    setRectSize(sf::Vector2f(w, h) * (float)SPRITE_SCALE);
}

// flip object
void Gobject::setFlip(bool newFlip){
    if(flipped != newFlip && doesFlipMirror){
        setRelativePos({-getRelativePos().x, getRelativePos().y});
    }
    flipped = newFlip;
    for(std::shared_ptr<Gobject> child : children) {
        child->setFlip(flipped);
    }
}

// make object be able to flip self
void Gobject::makeFlippable(){
    doesFlipMirror = 1;
}

// Getters
// relativePos
const sf::Vector2f& Gobject::getRelativePos(){
    return relativePos;
}
// selfRect
const sf::FloatRect& Gobject::getRect(){
    return selfRect;
}
// flipped
const bool& Gobject::isFlipped(){
    return flipped;
}