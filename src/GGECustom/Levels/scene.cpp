#include "inits.hpp"

#include "GGECustom/Gobjects/Bird.hpp"
#include "GGE/Gobjects/Sprite.hpp"
#include "GGECustom/Background/BackgroundManager.hpp"
#include "GGE/ResourceManager/ResourceManager.hpp"
#include "GGECustom/Pipes/PipesManager.hpp"
#include "GGECustom/GameConstants.hpp"

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
    bird->setRectPixelSize(24, 16);
    bird->setCurrentPos({100, (gge::GAME_HEIGHT - bird->getRect().getSize().y) / 2.f}, true);
    // sprite
    std::shared_ptr<gge::obj::Sprite> birdSprite = std::make_shared<gge::obj::Sprite>();
    bird->addChild(birdSprite);
    level->drawablesManager.newDrawable(birdSprite, false, 1);
    birdSprite->setTexture(level->resourceManager.getTexture("Assets/Textures/bird.png"));

    return level;
}