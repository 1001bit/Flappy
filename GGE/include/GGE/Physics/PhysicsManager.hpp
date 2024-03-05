#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"

#ifdef DRAW_COLLIDERS
#include "GGE/Gobjects/View.hpp"
#endif

namespace gge {

class PhysicsManager
{
private:
    static const ushort UPDATE_RATE;
    static const float GFORCE;
    static const float AIR_FRICTION;
    static const float GROUND_FRICTION;
    static const float ACCEL_COEFF;

    float accumulator;

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

    // Do all the physics stuff to all the bodies
    void updatePhysics(const float& dTimeMs);
    
public:
    // Structors
    PhysicsManager();
    ~PhysicsManager();

    // Methods
    // Update all including physics and interpolation
    void updateAll(const float& dTimeMs);

    // Interpolate all the kinematic bodies
    void interpolateKinematics(float alpha);

    // draw colliders
    #ifdef DRAW_COLLIDERS
    void drawColliders(sf::RenderWindow& window, std::shared_ptr<obj::View> levelView);
    #endif

    // Add new body to the vector
    void addNewBody(std::shared_ptr<obj::Body> body);
    void addNewBody(std::shared_ptr<obj::KinematicBody> body);
};

}