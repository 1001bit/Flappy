#include "GGE/SingletonManagers/CooldownsManager.hpp"

using gge::CooldownsManager;

// Singleton
CooldownsManager* CooldownsManager::instance = nullptr;
CooldownsManager* CooldownsManager::getInstance(){
    if (!instance)
        instance = new CooldownsManager();
    return instance;
}


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

// clean cooldowns vector
void CooldownsManager::clear(){
    cooldownsWeakVector.clear();
}