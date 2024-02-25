#pragma once

#include "GGE/Gobjects/Gobject.hpp"

#include "GGE/Physics/PhysicsManager.hpp"
#include "GGE/Instructions/TriggersManager.hpp"
#include "GGE/DrawablesManager/DrawablesManager.hpp"
#include "GGE/Cooldowns/CooldownsManager.hpp"
#include "GGE/ResourceManager/ResourceManager.hpp"

namespace gge {

class Level : public obj::Gobject
{
private:
    
public:
    // Structors
    Level();
    ~Level();

    ///////////////////////////
    // Managers
    TriggersManager triggersManager;
    PhysicsManager physicsManager;
    DrawablesManager drawablesManager;
    CooldownsManager cooldownsManager;
    ResourceManager resourceManager;

    // Updatable
    std::vector<std::weak_ptr<obj::Gobject>> updatableGobjects;
    // With own id
    std::unordered_map<uint16_t, std::weak_ptr<obj::Gobject>> gobjectIdMap;

    // Level view
    std::weak_ptr<obj::View> levelViewWeak;
    // Gui view
    std::weak_ptr<obj::View> guiViewWeak;
    ///////////////////////////

    // Methods
    // Init the level
    void init();
    // Update states of all the objects
    void update(const float& dTimeMs);
};

}