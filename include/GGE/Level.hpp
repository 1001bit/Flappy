#pragma once

#include "GGECustom/GameConstants.hpp"

#include "GGE/GObjects/GObject.hpp"
#include "GGE/GObjects/Camera.hpp"
#include "GGE/GObjects/Drawable.hpp"

#include "GGE/Physics/PhysicsManager.hpp"
#include "GGE/Instructions/TriggersManager.hpp"

#include "GGE/ResourceManager/ResourceManager.hpp"

// #define DRAWCOLLIDER

namespace gge {

class Level : public obj::GObject
{
private:
    // Gui
    sf::View guiView;
    
public:
    // Structors
    Level();
    ~Level();

    ///////////////////////////
    // Managers
    TriggersManager triggersManager;
    PhysicsManager physicsManager;

    // Updatable GObjects
    std::vector<std::weak_ptr<obj::GObject>> updatableGObjects;

    // Drawables
    std::vector< std::vector<std::weak_ptr<obj::Drawable>> > levelDrawableLayers;
    std::vector< std::vector<std::weak_ptr<obj::Drawable>> > guiDrawableLayers;

    // With own id
    std::unordered_map<uint16_t, std::weak_ptr<obj::GObject>> gObjectsWId;

    // Game camera that is following some GObject
    std::shared_ptr<obj::Camera> camera;
    ///////////////////////////

    // Methods
    // Init level
    void init();

    // Update states of all the objects
    void update(const float& dTimeMs);
    // Draw drawable objects
    void drawGObjetcs(sf::RenderWindow& window);
};

}