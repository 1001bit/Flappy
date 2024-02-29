#include "Instructions/TrCollision.hpp"

using gge::ins::TrCollision;

// Structors
TrCollision::TrCollision(std::weak_ptr<PipesManager> pipesManager, std::weak_ptr<obj::KinematicBody> body) : 
pipesManagerWeak(pipesManager), 
bodyWeak(body) 
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
    if(!bird || !pipesManager){
        return;
    }

    for (std::weak_ptr<obj::KinematicBody> pipeWeak : pipesManager->getPipes()){
        if(auto pipe = pipeWeak.lock()){
            if(pipe->getCurrentRect().intersects(bird->getCurrentRect())){
                activateActions();
                active = 0;
                return;
            }
        }
    }
}