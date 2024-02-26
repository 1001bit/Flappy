#pragma once

#include "Level.hpp"

namespace gge {

class LevelsManager
{
private:
    std::weak_ptr<Level> currentLevelWeak;
    std::unordered_map<ushort, std::shared_ptr<Level>> levelsMap;
    
public:
    // Structors
    LevelsManager();
    ~LevelsManager();

    // Methods
    // Set map level
    void setNewMapLevel(ushort id, std::shared_ptr<Level> level);
    // Load level from map by id
    void setCurrentLevel(ushort id);

    // Getters
    // currentLevelWeak
    std::weak_ptr<Level> getCurrentLevelWeak();
};

}