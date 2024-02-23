#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"
#include "GGE/Gobjects/Sprite.hpp"
#include "GGE/Level.hpp"

namespace gge {

class PipesManager : public obj::Gobject
{
private:
    std::vector<std::weak_ptr<obj::KinematicBody>> pipes;
    
public:
    std::weak_ptr<Level> levelWeak;
    bool moving;

    // Structors
    PipesManager();
    ~PipesManager();

    // Methods
    // Create top and bottom pipes
    void createNewPipePair();
    // Update
    void update(const float& dTimeMs);
};

}