#include "GGE/Physics/PhysicsManager.hpp"
#include "BaseHeaders/GameConstants.hpp"
#include "GGE/Controls/ControlsManager.hpp"
#include "GGE/MathHelper.hpp"

using gge::PhysicsManager;

// Structors
PhysicsManager::PhysicsManager(){
    active = true;
    accumulator = 0;
}

PhysicsManager::~PhysicsManager(){}

// Methods
// Update all including physics and interpolation
void PhysicsManager::updateAll(const float& dTimeMs){
    ControlsManager* controlsManager = ControlsManager::getInstance();

    accumulator += dTimeMs;
    while(accumulator >= 1000.f/UPDATE_RATE){
        updatePhysics(1000.f/UPDATE_RATE);
        accumulator -= 1000.f/UPDATE_RATE;

        // Controls
        controlsManager->clearPastBuffer();
    }
    interpolateKinematics(accumulator/(1000.f/UPDATE_RATE));
}

// Add new body to the vector of solid bodies
void PhysicsManager::addNewBody(std::shared_ptr<obj::Body> body){
    solidBodiesWeakVector.push_back(body);
}

void PhysicsManager::addNewBody(std::shared_ptr<obj::KinematicBody> body){
    kinematicBodiesWeakVector.push_back(body);
}

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