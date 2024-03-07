#include "GGE/Physics/PhysicsManager.hpp"
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
        if(kinematicBody->doApplyControl()){
            kinematicBody->control();
        }

        // gravity
        if(kinematicBody->doApplyGravity()){
            applyGravityToAccel(kinematicBody, dTimeMs);
        }

        // velocity += acceleration
        applyAccelerationToVel(kinematicBody, dTimeMs);

        // collide body with everything else
        if(kinematicBody->doApplyCollisions()){
            applyCollisions(kinematicBody);
        }

        // pos += velocity
        applyVelocityToPos(kinematicBody);
        
        // velocity *= friction
        if(kinematicBody->doApplyFriction()){
            applyFrictionToVel(kinematicBody);
        }

        ++it;
    }
}

// Apply gravity on all weigh objects
void PhysicsManager::applyGravityToAccel(std::shared_ptr<obj::KinematicBody> kinematicBody, const float& dTimeMs){
    kinematicBody->addAcceleration({0, GFORCE * dTimeMs});
}

// Apply the acceleration to the velocity
void PhysicsManager::applyAccelerationToVel(std::shared_ptr<obj::KinematicBody> kinematicBody, const float& dTimeMs){
    kinematicBody->addVelocity(kinematicBody->getAcceleration() * dTimeMs * ACCEL_COEFF);
    kinematicBody->setAcceleration({0,0});
}

// Apply the friction so body doesn't move for eternity
void PhysicsManager::applyFrictionToVel(std::shared_ptr<obj::KinematicBody> kinematicBody){
    if(kinematicBody->doApplyGravity()){
        // ground friction if platformer body is on ground
        if(kinematicBody->collisionDir.vertical == Direction::Down){
            kinematicBody->addVelocity({kinematicBody->getVelocity().x * -GROUND_FRICTION, 0});
        } 
        // air friction if platformer body is in air
        else {
            kinematicBody->addVelocity({kinematicBody->getVelocity().x * -AIR_FRICTION, 0});
        }
    } 
    // ground friction if floating body is on ground
    else {
        kinematicBody->addVelocity({kinematicBody->getVelocity().x * -GROUND_FRICTION, 0});
        kinematicBody->addVelocity({0, kinematicBody->getVelocity().y * -GROUND_FRICTION});
    }
}

// Apply the velocities of the bodies
void PhysicsManager::applyVelocityToPos(std::shared_ptr<obj::KinematicBody> kinematicBody){
    kinematicBody->moveCurrentRect(kinematicBody->getVelocity());
}