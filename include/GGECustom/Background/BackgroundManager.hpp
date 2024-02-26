#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"
#include "GGE/Gobjects/Sprite.hpp"
#include "GGE/ResourceManager/ResourceManager.hpp"
#include "GGE/Level/Level.hpp"

namespace gge{

class BackgroundManager : public obj::Gobject
{
private:
    obj::Sprite backgroundSpriteBase;
    std::vector<std::weak_ptr<obj::KinematicBody>> backgrounds;
    
public:
    std::weak_ptr<Level> levelWeak;

    // Structors
    BackgroundManager();
    ~BackgroundManager();

    // Methods
    // Update
    void update(const float& dTimeMs);
    // make baseBackgroundSprite
    void initBackgroundSprite();
    // make new background
    void createNewBackground();
};

}