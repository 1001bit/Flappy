#include "GGE/Game.hpp"
#include "GGE/Controls/ControlsManager.hpp"
#include "Levels/inits.hpp"
#include "BaseHeaders/GameConstants.hpp"

void initControls(){
    gge::ControlsManager* controlsManager = gge::ControlsManager::getInstance();
    // Keyboard controls
    controlsManager->setControlsMap({
        { "jump", {{sf::Keyboard::Space, sf::Keyboard::E}, {sf::Mouse::Left}} },
    });
}

int main()
{
    srand(time(NULL));

    // init window
    sf::RenderWindow window(sf::VideoMode(gge::GAME_WIDTH, gge::GAME_HEIGHT), "Flappy", sf::Style::Close);
    window.setFramerateLimit(gge::MAX_FPS);

    // init the game
    gge::Game game = gge::Game();
    initControls();

    // init levels
    game.levelsManager.makeLevelByFunc(0, clvl::newScene);

    // start level
    game.levelsManager.setCurrentLevel(0);

    // start the main loop
    game.loop(window);

    return 0;
}