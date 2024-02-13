#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Cooldown.hpp"

namespace gge {

class CooldownsManager
{
private:
    // Singleton
    static CooldownsManager* instance;
    CooldownsManager(){};

    // Variables
    // all the cooldowns clones
    std::vector<std::weak_ptr<Cooldown>> cooldownsWeakVector;
    
public:
    // Methods
    // update all the cooldowns
    void updateCooldowns(const float& dTimeMs);
    // get newly created clone of cooldown at id
    std::shared_ptr<Cooldown> newCooldown(Cooldown cooldown);
    // clean cooldowns vector
    void clear();

    // Singleton
    static CooldownsManager* getInstance();
};

}