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
    // levelsMap[id] = level
    void makeLevel(ushort id, std::shared_ptr<Level> level);
    // levelsMap[id] = newLevel(func)
    void makeLevelByFunc(ushort id, plevelfunc levelFunc);

    // Load level from map by id
    void setCurrentLevel(ushort id);

    // Getters
    // currentLevelWeak
    std::weak_ptr<Level> getCurrentLevelWeak();
};

}