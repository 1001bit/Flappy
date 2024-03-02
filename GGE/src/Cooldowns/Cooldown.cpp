#include "GGE/Cooldowns/Cooldown.hpp"
#include <cstdlib>

using gge::Cooldown;

// Structors
Cooldown::Cooldown(float startValueMs) :
startValueMs(startValueMs)
{
    paused = false;
    currentValueMs = 0;
}
Cooldown::~Cooldown(){}

// Methods
// start count
void Cooldown::start(unsigned randomMs){
    if(currentValueMs > 0){
        return;
    }
    currentValueMs = startValueMs + rand() % randomMs;
}

void Cooldown::start(){
    if(currentValueMs > 0){
        return;
    }
    currentValueMs = startValueMs;
}


// set count to 0
void Cooldown::stop(){
    currentValueMs = 0;
}

// update cooldown value
void Cooldown::update(const float& dTimeMs){
    if(currentValueMs == 0 || paused){
        return;
    }

    currentValueMs -= dTimeMs;
    if(currentValueMs < 0){
        currentValueMs = 0;
    }
}

// Getters
// get currentValueMs
const float& Cooldown::getCurrentValueMs(){
    return currentValueMs;
}
