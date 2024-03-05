#pragma once

#include "GGE/Level/LevelsManager.hpp"

namespace gge {

class Game
{
private:
    // Methods
    // Handle window events
    void handleEvent(const sf::Event& event);

public:
    LevelsManager levelsManager;

    // Structors
    Game();
    ~Game();

    // Methods
    // Main game loop
    void loop(const uint winW, const uint winH, const uint maxFps, const uint minFps, const std::string& title);
};

}