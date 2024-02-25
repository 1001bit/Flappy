#pragma once

#include <vector>
#include <memory>
#include "Cooldown.hpp"

namespace gge {

class CooldownsManager
{
private:
    // Variables
    // all the cooldowns clones
    std::vector<std::weak_ptr<Cooldown>> cooldownsWeakVector;
    
public:
    // Structors
    CooldownsManager();
    ~CooldownsManager();

    // Methods
    // update all the cooldowns
    void updateCooldowns(const float& dTimeMs);
    // get newly created clone of cooldown at id
    std::shared_ptr<Cooldown> newCooldown(Cooldown cooldown);
    // clean cooldowns vector
    void clear();
};

}