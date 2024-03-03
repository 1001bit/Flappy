#include "GGE/Gobjects/Gobject.hpp"
#include "BaseHeaders/GameConstants.hpp"
#include <cmath>

using gge::obj::Gobject;

// Structors
Gobject::Gobject() {
    flipped = false;
    rectMirrorable = false;

    #ifdef SHOW_OBJ_COUNT
    changeObjCount(1);
    #endif
}

Gobject::Gobject(const Gobject&) : enable_shared_from_this() {
    #ifdef SHOW_OBJ_COUNT
    changeObjCount(1);
    #endif
}

Gobject::~Gobject() {
    #ifdef SHOW_OBJ_COUNT
    changeObjCount(-1);
    #endif
}

// Methods
#ifdef SHOW_OBJ_COUNT
// Change and show how many objects are there
void Gobject::changeObjCount(short num){
    static unsigned objCount = 0;
    objCount += num;
    std::cout << "Gobject count: " << objCount << "\n";
}
#endif

// Update the state of the object
void Gobject::update(const float&){}

// Set position relative to parent's position
void Gobject::setRelativePos(const sf::Vector2f &relativePos) {
    this->relativePos = relativePos;
    updatePos();
}

// move self by some distance
void Gobject::move(const sf::Vector2f &distance) {
    setRelativePos(getRelativePos() + distance);
}

// update everything related to position
void Gobject::updatePos() {
    sf::Vector2f zeroPoint;

    if (auto parent = parentWeak.lock()) {
        zeroPoint.x = parent->getRect().left;
        zeroPoint.y = parent->getRect().top;
    }

    selfRect.left = zeroPoint.x + relativePos.x;
    selfRect.top = zeroPoint.y + relativePos.y;

    // update children's position
    for (std::shared_ptr<Gobject> child : children) {
        child->updatePos();
    }
}

// Add a new child
void Gobject::addChild(std::shared_ptr<Gobject> child) {
    if (auto childOldParent = child->parentWeak.lock()) {
        childOldParent->removeChild(child);
    }

    child->parentWeak = shared_from_this();
    children.push_back(child);
    child->updatePos();
}

// Remove existing child
void Gobject::removeChild(std::shared_ptr<Gobject> child) {
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

// Destroy self
void Gobject::removeSelf() {
    if (auto parent = parentWeak.lock()) {
        parent->removeChild(shared_from_this());
    }
}

// set size of selfRect
void Gobject::setRectSize(const sf::Vector2f &size) {
    selfRect.width = size.x;
    selfRect.height = size.y;
}

// set size of selfRect in pixels
void Gobject::setRectPixelSize(float w, float h) {
    setRectSize(sf::Vector2f(w, h) * (float)SPRITE_SCALE);
}

// flip object
void Gobject::setFlip(bool flip){
    if(flip == isFlipped()){
        return;
    }
    flipped = flip;

    // flip all the children
    for(std::shared_ptr<Gobject> child : children) {
        child->setFlip(!child->isFlipped());
    }

    // mirror relative position to X axis
    if(rectMirrorable){
        setRelativePos({-getRelativePos().x, getRelativePos().y});
    }
}

// make object's rect mirror relativePos.x
void Gobject::makeRectMirrorable() {
    rectMirrorable = true;
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
bool Gobject::isFlipped(){
    return flipped;
}