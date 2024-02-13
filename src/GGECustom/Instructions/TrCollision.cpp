#include "GGECustom/Instructions/TrCollision.hpp"

using gge::ins::TrCollision;

// Structors
TrCollision::TrCollision(){}
TrCollision::~TrCollision(){}

// Methods
// check if collided
void TrCollision::checkEvent(){
    if(!active){
        return;
    }

    auto body1 = body1Weak.lock();
    auto body2 = body2Weak.lock();

    if(!body1 || !body2){
        return;
    }

    if(!body1->currentRect.intersects(body2->currentRect)){
        return;
    }

    action->doAction();

    active = 0;
}

// set two bodies that gonna collide
void TrCollision::setCollisionBodies(std::shared_ptr<gge::obj::KinematicBody> newBody1, std::shared_ptr<gge::obj::KinematicBody> newBody2){
    body1Weak = newBody1;
    body2Weak = newBody2;
}