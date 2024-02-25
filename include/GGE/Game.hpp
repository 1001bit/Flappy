#pragma once

#include "GGE/Level.hpp"
#include "GGE/Controls/ControlsManager.hpp"
#include "GGECustom/GameConstants.hpp"

namespace gge {

class Game
{
private:
    // Methods
    // Handle window events
    void handleEvent(const sf::Event& event);

public:
    // Structors
    Game();
    ~Game();

    // Methods
    // Main game loop
    void loop(sf::RenderWindow& window);

    // Variables
    // pointer to the level
    std::shared_ptr<Level> currentLevel;
};

}