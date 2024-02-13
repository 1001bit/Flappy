#include "GGE/Physics/PhysicsManager.hpp"

using gge::PhysicsManager;

// Functions
// collide current body with non-kinematic collidable body
void collideKinematicAndSolid(std::shared_ptr<gge::obj::KinematicBody> kinematicBody, std::shared_ptr<gge::obj::Body> solidBody){
    // future rect method (if futureKinematicRect in touches solidRect, in some direction and now kinematicRect doesn't, kinematicBody stops in this direction)
    const sf::FloatRect& kinematicRect = kinematicBody->currentRect;
    const sf::FloatRect& solidRect = solidBody->getRect();
    
    sf::FloatRect futureKinematicRect;

    futureKinematicRect = kinematicRect;
    // down
    if(kinematicBody->velocity.y > 0){
        futureKinematicRect.height += kinematicBody->velocity.y;
        if(futureKinematicRect.intersects(solidRect)){
            kinematicBody->setCurrentPosition({kinematicRect.left, solidRect.top - kinematicRect.height});
            kinematicBody->collisionDir.vertical = Direction::Down;
            kinematicBody->velocity.y = 0;
        }
    } 
    // up
    else if (kinematicBody->velocity.y < 0){
        futureKinematicRect.top += kinematicBody->velocity.y;
        futureKinematicRect.height -= kinematicBody->velocity.y;
        if(futureKinematicRect.intersects(solidRect)){
            kinematicBody->setCurrentPosition({kinematicRect.left, solidRect.top + solidRect.height});
            kinematicBody->collisionDir.vertical = Direction::Up;
            kinematicBody->velocity.y = 0;
        }
    }

    futureKinematicRect = kinematicRect;
    // right
    if(kinematicBody->velocity.x > 0){
        futureKinematicRect.width += kinematicBody->velocity.x;
        if(futureKinematicRect.intersects(solidRect)){
            kinematicBody->setCurrentPosition({solidRect.left - kinematicRect.width, kinematicRect.top});
            kinematicBody->collisionDir.horizontal = Direction::Right;
            kinematicBody->velocity.x = 0;
        }
    } 
    // left
    else if (kinematicBody->velocity.x < 0){
        futureKinematicRect.left += kinematicBody->velocity.x;
        futureKinematicRect.width -= kinematicBody->velocity.x;
        if(futureKinematicRect.intersects(solidRect)){
            kinematicBody->setCurrentPosition({solidRect.left + solidRect.width, kinematicRect.top});
            kinematicBody->collisionDir.horizontal = Direction::Left;
            kinematicBody->velocity.x = 0;
        }
    }
}

// Methods
// Collide all the objects
void PhysicsManager::applyCollisions(std::shared_ptr<obj::KinematicBody> kinematicBody){
    kinematicBody->collisionDir = {Direction::None, Direction::None};

    // collide body with other body 
    for(auto it = solidBodiesWeakVector.begin(); it != solidBodiesWeakVector.end();){
        auto solidBody = it->lock();

        // if other is null, other is current, other got no rect - next;
        if(!solidBody){
            it = solidBodiesWeakVector.erase(it);
            continue;
        }

        // collide current body with non-kinematic collidable body
        if(solidBody->isCollidable()){
            collideKinematicAndSolid(kinematicBody, solidBody);
        }

        ++it;
    }
}