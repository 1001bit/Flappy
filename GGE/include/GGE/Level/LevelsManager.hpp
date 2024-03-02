#pragma once

#include "Level.hpp"

namespace gge {

using plevelfunc = std::shared_ptr<Level>(*)();

class LevelsManager
{
private:
    std::weak_ptr<Level> currentLevelWeak;
    ushort currentLevelId;

    std::unordered_map<ushort, std::shared_ptr<Level>> levelsMap;
    std::unordered_map<ushort, plevelfunc> levelFuncsMap;
    
public:
    // Structors
    LevelsManager();
    ~LevelsManager();

    // Methods
    // levelsMap[id] = level
    void makeLevel(ushort id, std::shared_ptr<Level> level);
    // levelsMap[id] = newLevel(func) ; levelFuncsMap[id] = newLevel
    void makeLevelByFunc(ushort id, plevelfunc levelFunc);

    // Load level from map by id
    void setCurrentLevel(ushort id);

    // update current level
    void updateCurrentLevel(const float& dTimeMs, sf::RenderWindow& window);

    // restart current level with function or not
    void restartCurrentLevel();

    // Getters
    // currentLevelWeak
    std::weak_ptr<Level> getCurrentLevelWeak();
};

}