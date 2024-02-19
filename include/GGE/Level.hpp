#pragma once

#include "GGECustom/GameConstants.hpp"

#include "GGE/GObjects/GObject.hpp"
#include "GGE/GObjects/SmoothFollower.hpp"
#include "GGE/GObjects/Drawable.hpp"

#include "GGE/Physics/PhysicsManager.hpp"
#include "GGE/Instructions/TriggersManager.hpp"
#include "GGE/DrawablesManager/DrawablesManager.hpp"

#include "GGE/ResourceManager/ResourceManager.hpp"

// #define DRAWCOLLIDER

namespace gge {

class Level : public obj::GObject
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

    // Updatable
    std::vector<std::weak_ptr<obj::GObject>> updatableGObjects;
    // With own id
    std::unordered_map<uint16_t, std::weak_ptr<obj::GObject>> gObjectsWId;

    // Game camera that is following some GObject
    std::weak_ptr<obj::SmoothFollower> cameraWeak;
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