#pragma once

#include <vector>
#include "GGE/Gobjects/KinematicBody.hpp"
#include "GGE/MathHelper.hpp"

namespace gge {

class PhysicsManager
{
private:
    // Variables
    // Bodies vector
    std::vector<std::weak_ptr<obj::Body>> solidBodiesWeakVector;
    // Kinematic bodies vector
    std::vector<std::weak_ptr<obj::KinematicBody>> kinematicBodiesWeakVector;

    // Methods
    // Manage collisions of all the bodies with each others
    void applyCollisions(std::shared_ptr<obj::KinematicBody> kinematicBody); 

    // Apply gravity on all weigh objects
    void applyGravityToAccel(std::shared_ptr<obj::KinematicBody> kinematicBody, const float& dTimeMs);
    
    // Apply the acceleration to the velocity
    void applyAccelerationToVel(std::shared_ptr<obj::KinematicBody> kinematicBody, const float& dTimeMs);
    // Apply the friction so body doesn't move for eternity
    void applyFrictionToVel(std::shared_ptr<obj::KinematicBody> kinematicBody);

    // Apply the velocities of the bodies
    void applyVelocityToPos(std::shared_ptr<obj::KinematicBody> kinematicBody);
    
public:
    // Structors
    PhysicsManager();
    ~PhysicsManager();

    // Methods
    // Do all the physics stuff to all the bodies
    void updatePhysics(const float& dTimeMs);

    // Interpolate all the kinematic bodies
    void interpolateKinematics(float alpha);

    // Add new body to the vector
    void addNewBody(std::shared_ptr<obj::Body> newBody);
    void addNewBody(std::shared_ptr<obj::KinematicBody> newBody);
};

}