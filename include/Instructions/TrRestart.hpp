#pragma once

#include "GGE/Instructions/Trigger.hpp"
#include "Gobjects/Bird.hpp"

namespace gge::ins {

// Some random trigger
class TrRestart : public Trigger
{
private:
    std::weak_ptr<obj::Bird> birdWeak;

public:
    // Structors
    TrRestart(std::shared_ptr<obj::Bird> bird);
    ~TrRestart();

    // Methods
    // checks if restart condition has happened
    void checkEvent();
};

}
