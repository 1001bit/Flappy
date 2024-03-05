#include "GGE/Game.hpp"
#include "GGE/Controls/ControlsManager.hpp"

using gge::Game;

// Structors
Game::Game(){}
Game::~Game(){}

// Methods
// Main loop
void Game::loop(const uint winW, const uint winH, const uint maxFps, const uint minFps, const std::string& title){
    sf::RenderWindow window(sf::VideoMode(winW, winH), title, sf::Style::Close);
    window.setFramerateLimit(maxFps);
    window.setKeyRepeatEnabled(false);

    ControlsManager* controlsManager = ControlsManager::getInstance();

    sf::Clock clock;
    while (window.isOpen())
    {
        // Time
        sf::Time deltaTime = clock.restart();
        float dTimeMs = deltaTime.asMicroseconds()/1000.0;
        // Limit max dt
        if(dTimeMs > 1000.f/minFps){
            #ifdef SHOW_FPS_SPIKES
            std::cout << "dTimeMs spike: " << dTimeMs << "\n";
            #endif

            dTimeMs = 1000.f/minFps;
        }
        #ifdef SHOW_FPS
        std::cout << "dTime (ms): " << dTimeMs << " ; \t\t" << " FPS: " << 1000/dTimeMs << "\n";
        #endif

        // Events and controls
        controlsManager->update();

        sf::Event event;
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            handleEvent(event);
        }

        levelsManager.updateCurrentLevel(dTimeMs, window);
    }
}

// handle window events
void Game::handleEvent(const sf::Event& event){
    ControlsManager* controlsManager = ControlsManager::getInstance();
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        controlsManager->controlPress(event.key.code);
        break;
    case sf::Event::MouseButtonPressed:
        controlsManager->controlPress(event.mouseButton.button);
        break;

    case sf::Event::KeyReleased:
        controlsManager->controlRelease(event.key.code);
        break;
    case sf::Event::MouseButtonReleased:
        controlsManager->controlRelease(event.mouseButton.button);

    default:
        break;
    }
}