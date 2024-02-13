#include "GGE/Game.hpp"

using gge::Game;

// Structors
Game::Game(){}

Game::~Game(){}

// Methods

// Game init
void Game::init(){
    // Level
    currentLevel = std::make_shared<Level>();
    currentLevel->init();
}

// Main loop
void Game::loop(sf::RenderWindow& window){
    window.setKeyRepeatEnabled(false);

    ControlsManager* controlsManager = ControlsManager::getInstance();
    CooldownsManager* cooldownsManager = CooldownsManager::getInstance();

    float accumulator = 0;

    sf::Clock clock;
    float dTimeMs;
    while (window.isOpen())
    {
        // Time
        sf::Time deltaTime = clock.restart();
        dTimeMs = deltaTime.asMicroseconds()/1000.0;
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

        // Events and controls
        controlsManager->clearPressed();

        sf::Event event;
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            handleEvent(event);
        }

        // Updates
        // Cooldowns
        cooldownsManager->updateCooldowns(dTimeMs);

        // Physics
        accumulator += dTimeMs;
        while(accumulator >= 1000.f/UPDATE_RATE){
            currentLevel->physicsManager.updatePhysics(1000.f/UPDATE_RATE);
            accumulator -= 1000.f/UPDATE_RATE;
        }
        currentLevel->physicsManager.interpolateKinematics(accumulator/(1000.f/UPDATE_RATE));

        // Triggers
        currentLevel->triggersManager.update();

        // GObjects that are level's children
        currentLevel->update(dTimeMs);

        //////////
        // Custom
        // Dialogues
        currentLevel->dialogueManager.updateCurrentDialogue(currentLevel->levelGObjectsWId, currentLevel->camera);
        //////////

        // Draw
        window.clear();
        currentLevel->drawGObjetcs(window);
        window.display();
    }
}

// handle window events
void Game::handleEvent(const sf::Event& event){
    ControlsManager* controlsManager = ControlsManager::getInstance();
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        controlsManager->addPressedKeyboard(event.key.code);
        break;
    case sf::Event::MouseButtonPressed:
        controlsManager->addPressedMouse(event.mouseButton.button);
        break;

    case sf::Event::KeyReleased:
        controlsManager->keyboardControlRelease(event.key.code);
        break;
    case sf::Event::MouseButtonReleased:
        controlsManager->mouseControlRelease(event.mouseButton.button);

    default:
        break;
    }
}