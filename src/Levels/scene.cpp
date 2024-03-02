#include "inits.hpp"

#include "Gobjects/Bird.hpp"
#include "GGE/Gobjects/Sprite.hpp"
#include "Background/BackgroundManager.hpp"
#include "GGE/ResourceManager/ResourceManager.hpp"
#include "Pipes/PipesManager.hpp"
#include "BaseHeaders/GameConstants.hpp"
#include "Instructions/AcRestart.hpp"
#include "Instructions/TrCollision.hpp"

std::shared_ptr<gge::Level> clvl::newScene(){
    std::shared_ptr<gge::Level> level = std::make_shared<gge::Level>();
    level->init();

    // background
    std::shared_ptr<gge::BackgroundManager> backgroundManager = std::make_shared<gge::BackgroundManager>(level);
    level->addChild(backgroundManager);
    level->updatableGobjects.push_back(backgroundManager);
    backgroundManager->initBackgroundSprite();

    // pipes
    std::shared_ptr<gge::PipesManager> pipesManager = std::make_shared<gge::PipesManager>(level);
    level->addChild(pipesManager);
    level->updatableGobjects.push_back(pipesManager);
    pipesManager->initCooldowns(level->cooldownsManager);
    pipesManager->initPipeSprite();

    // bird
    std::shared_ptr<gge::obj::Bird> bird = std::make_shared<gge::obj::Bird>();
    level->physicsManager.addNewBody(std::static_pointer_cast<gge::obj::KinematicBody>(bird));
    level->addChild(bird);
    bird->setRectPixelSize(22, 14);
    bird->setCurrentPos({100, (gge::GAME_HEIGHT - bird->getRect().getSize().y) / 2.f}, true);
    // sprite
    std::shared_ptr<gge::obj::Sprite> birdSprite = std::make_shared<gge::obj::Sprite>();
    bird->addChild(birdSprite);
    level->drawablesManager.newDrawable(birdSprite, false, 1);
    birdSprite->setTexture(level->resourceManager.getTexture("Assets/Textures/bird.png"));
    birdSprite->setRelativePos(-sf::Vector2f(1, 1) * gge::SPRITE_SCALE);

    // instructions
    // action
    std::shared_ptr<gge::ins::AcRestart> action = std::make_shared<gge::ins::AcRestart>(level);
    level->instructionsManager.actionsVector.push_back(action);

    std::shared_ptr<gge::ins::TrCollision> trigger = std::make_shared<gge::ins::TrCollision>(pipesManager, bird);
    level->instructionsManager.triggersVector.push_back(trigger);
    trigger->addAction(action);

    return level;
}