#include "Instructions/AcRestart.hpp"

using gge::ins::AcRestart;

// Structors
AcRestart::AcRestart(std::weak_ptr<PipesManager> pipesManager, std::weak_ptr<obj::KinematicBody> body, std::weak_ptr<Level> level) :
pipesManagerWeak(pipesManager),
bodyWeak(body),
levelWeak(level)
{}
AcRestart::~AcRestart(){}

// Methods
// restart the level
void AcRestart::activate(){
    auto pipesManager = pipesManagerWeak.lock();
    auto bird = bodyWeak.lock();
    auto level = levelWeak.lock();

    if(!(pipesManager && bird && level)){
        return;
    }

    level->restart = true;
}