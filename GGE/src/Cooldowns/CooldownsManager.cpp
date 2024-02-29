#include "GGE/Cooldowns/CooldownsManager.hpp"

using gge::CooldownsManager;

// Structors
CooldownsManager::CooldownsManager(){}
CooldownsManager::~CooldownsManager(){}

// Methods
// update all the cooldowns
void CooldownsManager::updateCooldowns(const float& dTimeMs){
    for(auto it = cooldownsWeakVector.begin(); it != cooldownsWeakVector.end();){
        std::shared_ptr<Cooldown> cooldown = it->lock();
        if(!cooldown){
            it = cooldownsWeakVector.erase(it);
            continue;
        }
        cooldown->update(dTimeMs);
        ++it;
    }
};

// get newly created clone of cooldown at id
std::shared_ptr<gge::Cooldown> CooldownsManager::newCooldown(Cooldown cooldown){
    std::shared_ptr<Cooldown> newCooldown = std::make_shared<Cooldown>(cooldown);
    cooldownsWeakVector.push_back(newCooldown);
    return newCooldown;
};