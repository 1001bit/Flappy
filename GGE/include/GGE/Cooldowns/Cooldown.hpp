#pragma once

namespace gge {

class Cooldown
{
private:
    float currentValueMs;
    float startValueMs;
    
public:
    bool paused;

    // Structors
    Cooldown(float startValueMs);
    ~Cooldown();

    // Methods
    // start count
    void start(unsigned randomMs);
    void start();
    // set count to 0
    void stop();
    // update cooldown
    void update(const float& dTimeMs);

    // Getters
    // get currentValueMs
    const float& getCurrentValueMs();
};

}