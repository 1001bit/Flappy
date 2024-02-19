#pragma once

#include "GObject.hpp"
#include "View.hpp"
#include <GGE/MathHelper.hpp>

namespace gge::obj {

class SmoothFollower : public GObject
{
private:
    // Variables
    std::weak_ptr<GObject> followTargetWeak;
    
public:
    // Structors
    SmoothFollower();
    ~SmoothFollower();

    // Methods
    // smoothly move camera
    void update(const float& dTimeMs);
    // set target of following
    void setTarget(std::shared_ptr<GObject> newTarget);
};

}