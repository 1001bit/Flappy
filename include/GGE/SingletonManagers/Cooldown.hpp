#pragma once

#include <iostream>
#include <cstdlib>

namespace gge {

class Cooldown
{
private:
    float currentValueMs;
    float startValueMs;
public:
    // Structors
    Cooldown(float newStartValueMs);
    ~Cooldown();

    // Methods
    // start count
    void start(unsigned randomMs);
    // set count to 0
    void stop();
    // update cooldown
    void update(const float& dTimeMs);

    // Getters
    // get currentValueMs
    const float& getCurrentValueMs();
};

}