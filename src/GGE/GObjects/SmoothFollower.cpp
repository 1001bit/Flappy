#include "GGE/GObjects/SmoothFollower.hpp"

using gge::obj::SmoothFollower;

constexpr float FACTOR = 0.98;

// Structors
SmoothFollower::SmoothFollower(){}

SmoothFollower::~SmoothFollower(){}

// Methods
// Smooth movement
void SmoothFollower::update(const float& dTimeMs){
    auto followTarget = followTargetWeak.lock();

    if(!followTarget){
        return;
    }

    const sf::FloatRect& targetRect = followTarget->getRect();
    sf::Vector2f targetCenterPos(targetRect.getPosition() + targetRect.getSize()/2.f);

    float blend = pow(FACTOR, dTimeMs);
    setRelativePos(lerp(targetCenterPos, getRelativePos(), blend));
    // setRelativePos(targetCenterPos);
}

// set target of following
void SmoothFollower::setTarget(std::shared_ptr<GObject> newTarget){
    followTargetWeak = newTarget;
};