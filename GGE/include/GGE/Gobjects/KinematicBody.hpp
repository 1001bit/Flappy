#pragma once

#include "Body.hpp"

namespace gge{
    struct CollisionDirection {
        Direction vertical;
        Direction horizontal;
    };  
}

namespace gge::obj {

class KinematicBody : public Body
{
private:
    sf::FloatRect currentRect;
    sf::FloatRect previousRect;

protected:
    bool weighs;
    bool friction;

public:
    sf::Vector2f acceleration;
    sf::Vector2f velocity;
    CollisionDirection collisionDir;  

    // Methods
    // Control the body
    virtual void control();
    // Accelerate the body
    void accelerate(float accelX, float accelY);
    // Set the position of the current rect. If teleport, it moves everything else with currentRect
    void setCurrentPos(const sf::Vector2f& pos, bool teleport = false);
    // Move the current rect
    void moveCurrentRect(const sf::Vector2f& moveDistance);
    // set size of current rect
    void setRectSize(const sf::Vector2f& size);
    // set previousRect = currentRect
    void updatePreviousRect();

    // Getters
    // weighs
    const bool& doesWeigh();
    // friction
    const bool& doesFriction();
    // currentRect
    const sf::FloatRect& getCurrentRect();
    // previousRect
    const sf::FloatRect& getPreviousRect();

    // Structors
    KinematicBody();
    ~KinematicBody();
};

}