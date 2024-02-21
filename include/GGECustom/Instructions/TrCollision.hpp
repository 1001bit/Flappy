#pragma once

#include "GGE/Instructions/Trigger.hpp"
#include "GGE/Gobjects/KinematicBody.hpp"

namespace gge::ins {

// Some random trigger
class TrCollision : public Trigger
{
private:
    // Variables
    std::weak_ptr<gge::obj::KinematicBody> body1Weak;
    std::weak_ptr<gge::obj::KinematicBody> body2Weak;

public:
    // Structors
    TrCollision();
    ~TrCollision();

    // Methods
    // checks if some bodies collided
    void checkEvent();
    // Set 2 bodies
    void setCollisionBodies(std::shared_ptr<gge::obj::KinematicBody> newBody1, std::shared_ptr<gge::obj::KinematicBody> newBody2);
};

}
