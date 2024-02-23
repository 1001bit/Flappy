#include "inits.hpp"

#include "GGECustom/Gobjects/Bird.hpp"
#include "GGE/Gobjects/Sprite.hpp"

void clvl::scene(std::shared_ptr<gge::Level> level){
    gge::ResourceManager* resourceManager = gge::ResourceManager::getInstance();

    // background
    std::shared_ptr<gge::obj::Sprite> background = std::make_shared<gge::obj::Sprite>();
    level->addChild(background);
    level->drawablesManager.newDrawable(background, 0, 0);
    background->setTexture(resourceManager->getTexture("Assets/Textures/background.png"));

    // pipes
    std::shared_ptr<gge::PipesManager> pipesManager = std::make_shared<gge::PipesManager>();
    level->addChild(pipesManager);
    level->updatableGobjects.push_back(pipesManager);
    pipesManager->levelWeak = level;
    pipesManager->createNewPipePair();

    // bird
    std::shared_ptr<gge::obj::Bird> bird = std::make_shared<gge::obj::Bird>();
    level->physicsManager.addNewBody(std::static_pointer_cast<gge::obj::KinematicBody>(bird));
    level->addChild(bird);
    bird->setRectPixelSize(24, 16);
    bird->setCurrentPos({100, (gge::GAME_HEIGHT - bird->getRect().getSize().y) / 2.f});
    // sprite
    std::shared_ptr<gge::obj::Sprite> birdSprite = std::make_shared<gge::obj::Sprite>();
    bird->addChild(birdSprite);
    level->drawablesManager.newDrawable(birdSprite, 0, 1);
    birdSprite->setTexture(resourceManager->getTexture("Assets/Textures/bird.png"));
}