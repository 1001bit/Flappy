#include "GGE/Game.hpp"
#include "GGE/Controls/ControlsManager.hpp"
#include "GGE/Gobjects/Sprite.hpp"
#include "Levels/inits.hpp"

const float gge::obj::Sprite::SPRITE_SCALE = 4;

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

    // init the game
    gge::Game game = gge::Game();
    initControls();

    // init levels
    game.levelsManager.makeLevelByFunc(0, clvl::newScene);

    // start level
    game.levelsManager.setCurrentLevel(0);

    // start the main loop
    game.loop(480, 720, 150, 120, "Flappy");

    return 0;
}