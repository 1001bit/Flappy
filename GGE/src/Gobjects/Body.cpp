#include "GGE/Gobjects/Body.hpp"

using gge::obj::Body;

// Structors
Body::Body(){
    applyCollisions = 1;
}

Body::~Body(){}

// Getters
// collidable
const bool& Body::doApplyCollisions(){
    return applyCollisions;
}