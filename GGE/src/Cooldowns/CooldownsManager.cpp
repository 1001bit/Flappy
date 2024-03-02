#include "GGE/Cooldowns/CooldownsManager.hpp"

using gge::CooldownsManager;

// Structors
CooldownsManager::CooldownsManager(){}
CooldownsManager::~CooldownsManager(){}

// Methods
// update all the cooldowns
void CooldownsManager::updateCooldowns(const float& dTimeMs){
    for(auto it = cooldownsWeak.begin(); it != cooldownsWeak.end();){
        std::shared_ptr<Cooldown> cooldown = it->lock();
        if(!cooldown){
            it = cooldownsWeak.erase(it);
            continue;
        }

        cooldown->update(dTimeMs);

        ++it;
    }
};

// pause all the cooldowns
void CooldownsManager::pauseCooldowns(){
    for(auto it = cooldownsWeak.begin(); it != cooldownsWeak.end();){
        std::shared_ptr<Cooldown> cooldown = it->lock();
        if(!cooldown){
            it = cooldownsWeak.erase(it);
            continue;
        }

        cooldown->paused = true;
        pausedCooldownsWeak.push_back(cooldown);

        ++it;
    }
}

// resume all the cooldowns
void CooldownsManager::resumeCooldowns(){
    for(auto it = pausedCooldownsWeak.begin(); it != pausedCooldownsWeak.end();){
        if(auto cooldown = it->lock()){
            cooldown->paused = false;
        }
        ++it;
    }
    pausedCooldownsWeak.clear();
}

// get newly created clone of cooldown at id
std::shared_ptr<gge::Cooldown> CooldownsManager::newCooldown(Cooldown cooldown){
    std::shared_ptr<Cooldown> newCooldown = std::make_shared<Cooldown>(cooldown);
    cooldownsWeak.push_back(newCooldown);
    return newCooldown;
};