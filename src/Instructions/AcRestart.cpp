#include "Instructions/AcRestart.hpp"

using gge::ins::AcRestart;

// Structors
AcRestart::AcRestart(std::weak_ptr<Level> level) :
levelWeak(level)
{}
AcRestart::~AcRestart(){}

// Methods
// restart the level
void AcRestart::activate(){
    if(auto level = levelWeak.lock()){
        level->restart();
    }
}