#include "GGE/Physics/PhysicsManager.hpp"
#include "BaseHeaders/GameConstants.hpp"
#include "GGE/MathHelper.hpp"

using gge::PhysicsManager;

// Methods
// Do all the physics stuff to all the bodies
void PhysicsManager::updatePhysics(const float& dTimeMs){
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
        if(kinematicBody->isCollidable()){
            kinematicBody->control();
        }

        // gravity
        if(kinematicBody->doesWeigh()){
            applyGravityToAccel(kinematicBody, dTimeMs);
        }

        // velocity += acceleration
        applyAccelerationToVel(kinematicBody, dTimeMs);

        // collide body with everything else
        if(kinematicBody->isCollidable()){
            applyCollisions(kinematicBody);
        }

        // pos += velocity
        applyVelocityToPos(kinematicBody);
        
        // velocity *= friction
        if(kinematicBody->doesFriction()){
            applyFrictionToVel(kinematicBody);
        }

        ++it;
    }
}

// Apply gravity on all weigh objects
void PhysicsManager::applyGravityToAccel(std::shared_ptr<obj::KinematicBody> kinematicBody, const float& dTimeMs){
    kinematicBody->accelerate(0, GFORCE * dTimeMs);
}

// Apply the acceleration to the velocity
void PhysicsManager::applyAccelerationToVel(std::shared_ptr<obj::KinematicBody> kinematicBody, const float& dTimeMs){
    kinematicBody->velocity += kinematicBody->acceleration * dTimeMs * ACCEL_COEFF;
    kinematicBody->acceleration = sf::Vector2f();
}

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
}