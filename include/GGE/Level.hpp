#pragma once

#include "GGE/GameConstants.hpp"

#include "GGE/GObjects/GObject.hpp"
#include "GGE/GObjects/AnimatedSprite.hpp"
#include "GGE/GObjects/Sprite.hpp"
#include "GGECustom/GObjects/PhysPlayer.hpp"
#include "GGE/GObjects/Camera.hpp"
#include "GGE/GObjects/Body.hpp"
#include "GGECustom/GObjects/TDPlayer.hpp"
#include "GGECustom/GObjects/TDNpc.hpp"
#include "GGECustom/GObjects/PhysNpc.hpp"
#include "GGE/GObjects/Text.hpp"
#include "GGE/GObjects/Drawable.hpp"

#include "GGECustom/Dialogues/DialogueManager.hpp"
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
    //////////
    // Custom
    DialogueManager dialogueManager;
    //////////

    // Updatable GObjects
    std::vector<std::weak_ptr<obj::GObject>> updatableGObjects;

    // Drawables
    std::vector< std::vector<std::weak_ptr<obj::Drawable>> > levelDrawableLayers;
    std::vector< std::vector<std::weak_ptr<obj::Drawable>> > guiDrawableLayers;

    // With own id
    std::unordered_map<uint16_t, std::weak_ptr<obj::GObject>> levelGObjectsWId;

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