#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"
#include "GGE/Gobjects/Sprite.hpp"
#include "GGE/ResourceManager/ResourceManager.hpp"
#include "GGE/Level/Level.hpp"

namespace gge{

class BackgroundManager : public obj::Gobject
{
private:
    static const float BACKGROUND_SPEED;

    std::vector<std::weak_ptr<obj::KinematicBody>> backgrounds;
    std::weak_ptr<Level> levelWeak;
    
public:
    // Structors
    BackgroundManager(std::shared_ptr<Level> level);
    ~BackgroundManager();

    // Methods
    // Update
    void update(const float& dTimeMs);
    // make start bacgrounds
    void init();
    // make new background
    void createNewBackground();
};

}