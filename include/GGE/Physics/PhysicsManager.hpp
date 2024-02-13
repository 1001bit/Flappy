#pragma once

#include <vector>
#include "GGE/GObjects/KinematicBody.hpp"
#include "GGE/MathHelper.hpp"

constexpr float GFORCE = 0.08;
constexpr float AIR_FRICTION = 0.015;
constexpr float GROUND_FRICTION = 0.3;
constexpr float ACCEL_COEFF = 0.1;

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

    // Add new body to the solids vector
    void addNewSolidBody(std::shared_ptr<obj::Body> newBody);
    // Add new body to the kinematics vector
    void addNewKinematicBody(std::shared_ptr<obj::KinematicBody> newBody);
};

}