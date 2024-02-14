#include "GGE/Game.hpp"

#include "GGECustom/Levels/inits.hpp"

void initControls(){
    gge::ControlsManager* controlsManager = gge::ControlsManager::getInstance();
    // Keyboard controls
    controlsManager->setKeyboardControlsMap({
        {"jump", sf::Keyboard::Space},
    });
}

int main()
{
    srand(time(NULL));

    // init window
    sf::RenderWindow window(sf::VideoMode(gge::GAME_WIDTH, gge::GAME_HEIGHT), "GoodGame test", sf::Style::Close);
    window.setFramerateLimit(gge::MAX_FPS);

    // init the game
    std::shared_ptr<gge::Game> game = std::make_shared<gge::Game>();
    game->init();
    initControls();

    // init levels
    std::shared_ptr<gge::Level> level = game->currentLevel;
    clvl::scene(level);

    // start the main loop
    game->loop(window);

    return 0;
}