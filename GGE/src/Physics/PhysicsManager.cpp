#include "GGE/Physics/PhysicsManager.hpp"
#include "BaseHeaders/GameConstants.hpp"
#include "GGE/MathHelper.hpp"

using gge::PhysicsManager;

// Structors
PhysicsManager::PhysicsManager(){
    active = true;
}

PhysicsManager::~PhysicsManager(){}

// Methods
// Do all the physics stuff to all the bodies
void PhysicsManager::updatePhysics(const float& dTimeMs){
    if(!active){
        return;
    }

    for(auto it = kinematicBodiesWeakVector.begin(); it != kinematicBodiesWeakVector.end();){
        auto kinematicBody = it->lock();
        // if current body is nil or no rect
        if(!kinematicBody){
            it = kinematicBodiesWeakVector.erase(it);
            continue;
        }

        // interpolation
        kinematicBody->updatePreviousRect();

        // control body (like player, npc)
        kinematicBody->control();

        if(kinematicBody->doesWeigh()){
            applyGravityToAccel(kinematicBody, dTimeMs);
        }

        applyAccelerationToVel(kinematicBody, dTimeMs);
        if(kinematicBody->isCollidable()){
            applyCollisions(kinematicBody);
        }
        applyVelocityToPos(kinematicBody);
        if(kinematicBody->doesFriction()){
            applyFrictionToVel(kinematicBody);
        }

        ++it;
    }
};

// Apply gravity on all weigh objects
void PhysicsManager::applyGravityToAccel(std::shared_ptr<obj::KinematicBody> kinematicBody, const float& dTimeMs){
    kinematicBody->accelerate(0, GFORCE * dTimeMs);
};

// Apply the acceleration to the velocity
void PhysicsManager::applyAccelerationToVel(std::shared_ptr<obj::KinematicBody> kinematicBody, const float& dTimeMs){
    kinematicBody->velocity += kinematicBody->acceleration * dTimeMs * ACCEL_COEFF;
    kinematicBody->acceleration = sf::Vector2f();
};

// Apply the friction so body doesn't move for eternity
void PhysicsManager::applyFrictionToVel(std::shared_ptr<obj::KinematicBody> kinematicBody){
    if(kinematicBody->doesWeigh()){
        // ground friction if platformer body is on ground
        if(kinematicBody->collisionDir.vertical == Direction::Down){
            kinematicBody->velocity.x -= kinematicBody->velocity.x * GROUND_FRICTION;
        } 
        // air friction if platformer body is in air
        else {
            kinematicBody->velocity.x -= kinematicBody->velocity.x * AIR_FRICTION;
        }
    } 
    // ground friction if floating body is on ground
    else {
        kinematicBody->velocity.x -= kinematicBody->velocity.x * GROUND_FRICTION;
        kinematicBody->velocity.y -= kinematicBody->velocity.y * GROUND_FRICTION;
    }
}

// Apply the velocities of the bodies
void PhysicsManager::applyVelocityToPos(std::shared_ptr<obj::KinematicBody> kinematicBody){
    kinematicBody->moveCurrentRect(kinematicBody->velocity);
};

// Add new body to the vector of solid bodies
void PhysicsManager::addNewBody(std::shared_ptr<obj::Body> body){
    solidBodiesWeakVector.push_back(body);
}

void PhysicsManager::addNewBody(std::shared_ptr<obj::KinematicBody> body){
    kinematicBodiesWeakVector.push_back(body);
}

//////////////////////////////////////////////
// Interpolate all the kinematic bodies
void PhysicsManager::interpolateKinematics(float alpha){
    for(auto it = kinematicBodiesWeakVector.begin(); it != kinematicBodiesWeakVector.end();){
        auto kinematicBody = it->lock();
        // if current body is nil or no rect
        if(!kinematicBody){
            it = kinematicBodiesWeakVector.erase(it);
            continue;
        }

        const sf::FloatRect& currentRect = kinematicBody->getCurrentRect();
        const sf::FloatRect& previousRect = kinematicBody->getPreviousRect();

        kinematicBody->setRelativePos(lerp(previousRect.getPosition(), currentRect.getPosition(), alpha));
        
        ++it;
    }
};