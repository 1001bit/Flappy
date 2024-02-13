#include "GGE/GObjects/GObject.hpp"

using gge::obj::GObject;

// Structors
GObject::GObject(){
    this->flipped = 0;
    this->doesFlipMirror = 0;
}

GObject::~GObject(){}

// Methods
void GObject::update(const float& dTimeMs){}

void GObject::updatePos(){
    sf::Vector2f zeroPoint;

    if(auto parent = parentWeak.lock()){
        zeroPoint.x = parent->getRect().left;
        zeroPoint.y = parent->getRect().top;
    }
    
    selfRect.left = zeroPoint.x + relativePos.x;
    selfRect.top = zeroPoint.y + relativePos.y;

    // update children's position
    for(std::shared_ptr<GObject> child : children) {
        child->updatePos();
    }
}

void GObject::addChild(std::shared_ptr<GObject> newChild){
    children.push_back(newChild);
    newChild->updatePos();
}

void GObject::removeChild(std::shared_ptr<GObject> child){
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

void GObject::setNewParent(std::shared_ptr<GObject> newParent){
    if(auto parent = parentWeak.lock()){
        parent->removeChild(shared_from_this());
    }

    this->parentWeak = newParent;
    newParent->addChild(shared_from_this());
}

void GObject::setRelativePos(const sf::Vector2f& newRelativePos){
    relativePos = newRelativePos;
    updatePos();
}

void GObject::move(const sf::Vector2f& distance){
    setRelativePos(getRelativePos() + distance);
}

void GObject::setRectSize(float w, float h){
    selfRect.width = w;
    selfRect.height = h;
}

void GObject::setRectPixelSize(float w, float h){
    setRectSize(w*SPRITE_SCALE, h*SPRITE_SCALE);
}

void GObject::setFlip(bool newFlip){
    if(flipped != newFlip && doesFlipMirror){
        setRelativePos({-getRelativePos().x, getRelativePos().y});
    }
    flipped = newFlip;
    for(std::shared_ptr<GObject> child : children) {
        child->setFlip(flipped);
    }
}

void GObject::makeFlippable(){
    doesFlipMirror = 1;
}

// Getters

const sf::Vector2f& GObject::getRelativePos(){
    return relativePos;
}

const sf::FloatRect& GObject::getRect(){
    return selfRect;
}

const bool& GObject::isFlipped(){
    return flipped;
}