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

    sf::Vector2f velocity;
    sf::Vector2f acceleration;

protected:
    bool applyGravity;
    bool applyFriction;
    bool applyControl;
    float maxVelocity;

public:
    CollisionDirection collisionDir;

    // Methods
    // Control the body
    virtual void control();

    // velocity = velocity
    void setVelocity(const sf::Vector2f& velocity);
    // velocity += velocity
    void addVelocity(const sf::Vector2f& velocity);
    // acceleration = acceleration
    void setAcceleration(const sf::Vector2f& acceleration);
    // acceleration += acceleration
    void addAcceleration(const sf::Vector2f& acceleration);

    // Set the position of the current rect. If teleport, it moves everything else with currentRect
    void setCurrentPos(const sf::Vector2f& pos, bool teleport = false);
    // Move the current rect
    void moveCurrentRect(const sf::Vector2f& moveDistance);
    // set size of current rect
    void setRectSize(const sf::Vector2f& size);
    // set previousRect = currentRect
    void updatePreviousRect();

    // Getters
    // applyGravity
    bool doApplyGravity();
    // applyFriction
    bool doApplyFriction();
    // applyControl
    bool doApplyControl();

    // velocity
    const sf::Vector2f& getVelocity();
    // acceleration
    const sf::Vector2f& getAcceleration();

    // currentRect
    const sf::FloatRect& getCurrentRect();
    // previousRect
    const sf::FloatRect& getPreviousRect();

    // Structors
    KinematicBody();
    ~KinematicBody();
};

}