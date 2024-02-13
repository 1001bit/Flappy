#include "GGE/Game.hpp"

#include "GGECustom/Levels/inits.hpp"

void initControls(){
    gge::ControlsManager* controlsManager = gge::ControlsManager::getInstance();
    // Keyboard controls
    controlsManager->setKeyboardControlsMap({
        {"wLeft", sf::Keyboard::A},
        {"wRight", sf::Keyboard::D},
        {"wUp", sf::Keyboard::W},
        {"wDown", sf::Keyboard::S},
        {"jump", sf::Keyboard::Space},
    });
    // mouse controls
    controlsManager->setMouseControlsMap({
        {"dialogueNext", sf::Mouse::Left}
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
    clvl::dialogueInit(level);
    clvl::testInit(level);

    // start the main loop
    game->loop(window);

    return 0;
}