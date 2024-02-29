#pragma once

#include "Level.hpp"

namespace gge {

using plevelfunc = std::shared_ptr<gge::Level>(*)();

class LevelsManager
{
private:
    std::weak_ptr<Level> currentLevelWeak;
    std::unordered_map<ushort, std::shared_ptr<Level>> levelsMap;
    std::unordered_map<ushort, plevelfunc> levelFuncsMap;
    
public:
    // Structors
    LevelsManager();
    ~LevelsManager();

    // Methods
    // levelsMap[id] = level
    void makeLevel(ushort id, std::shared_ptr<Level> level);
    // levelsFuncMap[id] = levelsFuncMap
    void makeLevelFunc(ushort id, plevelfunc levelFunc);
    // levelsMap[levelId] = levelsFuncMap[funcId]
    void makeLevelByFunc(ushort levelId, ushort funcId);

    // Load level from map by id
    void setCurrentLevel(ushort id);

    // Getters
    // currentLevelWeak
    std::weak_ptr<Level> getCurrentLevelWeak();
};

}