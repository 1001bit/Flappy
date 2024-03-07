#include "Instructions/TrCollision.hpp"

using gge::ins::TrCollision;

// Structors
TrCollision::TrCollision(std::shared_ptr<PipesManager> pipesManager, std::shared_ptr<obj::KinematicBody> body, std::shared_ptr<Level> level) : 
pipesManagerWeak(pipesManager), 
bodyWeak(body),
levelWeak(level)
{}
TrCollision::~TrCollision(){}

// Methods
// check if collided
void TrCollision::checkEvent(){
    if(!active){
        return;
    }

    auto bird = bodyWeak.lock();
    auto pipesManager = pipesManagerWeak.lock();
    auto level = levelWeak.lock();
    if(!bird || !pipesManager || !level){
        return;
    }
    auto levelView = level->levelViewWeak.lock();
    if(!levelView){
        return;
    }

    for (std::weak_ptr<obj::KinematicBody> pipeWeak : pipesManager->getPipes()){
        if(auto pipe = pipeWeak.lock()){
            // set both rect positions.y to 0 to check collisions even if bird too far away
            sf::FloatRect pipeRect = pipe->getRect();
            sf::FloatRect birdRect = bird->getRect();
            if(!levelView->getRect().intersects(birdRect)){
                birdRect.top = 0;
                pipeRect.top = 0;
            }

            if(pipeRect.intersects(birdRect)){
                activateActions();
                active = false;
                return;
            }
        }
    }
}