#include "GGE/Game.hpp"
#include "GGE/Controls/ControlsManager.hpp"
#include "GGECustom/GameConstants.hpp"

using gge::Game;

// Structors
Game::Game(){}

Game::~Game(){}

// Methods
// Main loop
void Game::loop(sf::RenderWindow& window){
    window.setKeyRepeatEnabled(false);

    ControlsManager* controlsManager = ControlsManager::getInstance();

    float accumulator = 0;

    sf::Clock clock;
    while (window.isOpen())
    {
        // Time
        sf::Time deltaTime = clock.restart();
        float dTimeMs = deltaTime.asMicroseconds()/1000.0;
        // Limit max dt
        if(dTimeMs > 1000.f/MIN_FPS){
            #ifdef SHOW_FPS_SPIKES
            std::cout << dTimeMs << "\n";
            #endif
            dTimeMs = 1000.f/MIN_FPS;
        }
        #ifdef SHOW_FPS
        std::cout << "dTime (ms): " << dTimeMs << " ; \t\t" << " FPS: " << 1000/dTimeMs << "\n";
        #endif

        // Controls
        controlsManager->updateBuffer();

        // Events
        sf::Event event;
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            handleEvent(event);
        }

        // Updates
        // Cooldowns
        currentLevel->cooldownsManager.updateCooldowns(dTimeMs);

        // Physics
        accumulator += dTimeMs;
        while(accumulator >= 1000.f/UPDATE_RATE){
            currentLevel->physicsManager.updatePhysics(1000.f/UPDATE_RATE);
            accumulator -= 1000.f/UPDATE_RATE;

            // Controls
            controlsManager->clearPastBuffer();
        }
        currentLevel->physicsManager.interpolateKinematics(accumulator/(1000.f/UPDATE_RATE));

        // Triggers
        currentLevel->triggersManager.update();

        // Gobjects that are level's children
        currentLevel->update(dTimeMs);

        // Draw
        window.clear();
        
        auto levelView = currentLevel->levelViewWeak.lock();
        auto guiView = currentLevel->guiViewWeak.lock();
        if(levelView && guiView){
            currentLevel->drawablesManager.draw(window, levelView, guiView);
        }

        window.display();
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