#include "GGE/Physics/PhysicsManager.hpp"

using gge::PhysicsManager;

// Functions
// collide current body with non-kinematic collidable body
void collideKinematicAndSolid(std::shared_ptr<gge::obj::KinematicBody> kinematicBody, std::shared_ptr<gge::obj::Body> solidBody){
    // future rect method (if futureKinematicRect in touches solidRect, in some direction and now kinematicRect doesn't, kinematicBody stops in this direction)
    const sf::FloatRect& kinematicRect = kinematicBody->getCurrentRect();
    const sf::FloatRect& solidRect = solidBody->getRect();
    
    sf::FloatRect futureKinematicRect;

    futureKinematicRect = kinematicRect;
    // down
    if(kinematicBody->getVelocity().y > 0){
        futureKinematicRect.height += kinematicBody->getVelocity().y;
        if(futureKinematicRect.intersects(solidRect)){
            kinematicBody->setCurrentPos({kinematicRect.left, solidRect.top - kinematicRect.height});
            kinematicBody->collisionDir.vertical = Direction::Down;
            kinematicBody->setVelocity({kinematicBody->getVelocity().x, 0});
        }
    } 
    // up
    else if (kinematicBody->getVelocity().y < 0){
        futureKinematicRect.top += kinematicBody->getVelocity().y;
        futureKinematicRect.height -= kinematicBody->getVelocity().y;
        if(futureKinematicRect.intersects(solidRect)){
            kinematicBody->setCurrentPos({kinematicRect.left, solidRect.top + solidRect.height});
            kinematicBody->collisionDir.vertical = Direction::Up;
            kinematicBody->setVelocity({kinematicBody->getVelocity().x, 0});
        }
    }

    futureKinematicRect = kinematicRect;
    // right
    if(kinematicBody->getVelocity().x > 0){
        futureKinematicRect.width += kinematicBody->getVelocity().x;
        if(futureKinematicRect.intersects(solidRect)){
            kinematicBody->setCurrentPos({solidRect.left - kinematicRect.width, kinematicRect.top});
            kinematicBody->collisionDir.horizontal = Direction::Right;
            kinematicBody->setVelocity({0, kinematicBody->getVelocity().y});
        }
    } 
    // left
    else if (kinematicBody->getVelocity().x < 0){
        futureKinematicRect.left += kinematicBody->getVelocity().x;
        futureKinematicRect.width -= kinematicBody->getVelocity().x;
        if(futureKinematicRect.intersects(solidRect)){
            kinematicBody->setCurrentPos({solidRect.left + solidRect.width, kinematicRect.top});
            kinematicBody->collisionDir.horizontal = Direction::Left;
            kinematicBody->setVelocity({0, kinematicBody->getVelocity().y});
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
        if(solidBody->doApplyCollisions()){
            collideKinematicAndSolid(kinematicBody, solidBody);
        }

        ++it;
    }
}

// Draw colliders
#ifdef DRAW_COLLIDERS
void PhysicsManager::drawColliders(sf::RenderWindow& window, std::shared_ptr<obj::View> levelView){
    window.setView(levelView->getView());
    
    // Solid
    for(auto it = solidBodiesWeakVector.begin(); it != solidBodiesWeakVector.end();){
        auto body = it->lock();
        if(!body){
            it = solidBodiesWeakVector.erase(it);
            continue;
        }

        sf::RectangleShape colliderRect(body->getRect().getSize());
        colliderRect.setPosition(body->getRect().getPosition());
        colliderRect.setFillColor(sf::Color(0, 255, 0, 130));
        window.draw(colliderRect);

        ++it;
    }

    // Kinematic
    for(auto it = kinematicBodiesWeakVector.begin(); it != kinematicBodiesWeakVector.end();){
        auto body = it->lock();
        if(!body){
            it = kinematicBodiesWeakVector.erase(it);
            continue;
        }

        sf::RectangleShape colliderRect(body->getCurrentRect().getSize());
        colliderRect.setPosition(body->getCurrentRect().getPosition());
        colliderRect.setFillColor(sf::Color(255, 0, 0, 130));
        window.draw(colliderRect);

        ++it;
    }
}
#endif