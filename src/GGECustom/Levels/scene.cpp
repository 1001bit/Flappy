#include "inits.hpp"

#include "GGECustom/GObjects/Bird.hpp"
#include "GGE/GObjects/Sprite.hpp"

void clvl::scene(std::shared_ptr<gge::Level> level){
    gge::ResourceManager* resourceManager = gge::ResourceManager::getInstance();

    // background
    std::shared_ptr<gge::obj::Sprite> background = std::make_shared<gge::obj::Sprite>();
    level->addChild(background);
    level->drawablesManager.newDrawable(background, 0, 0);
    background->setTexture(resourceManager->getTexture("Assets/Textures/background.png"));

    // pipe
    std::shared_ptr<gge::obj::Sprite> pipe = std::make_shared<gge::obj::Sprite>();
    level->addChild(pipe);
    level->drawablesManager.newDrawable(pipe, 0, 0);
    pipe->setTexture(resourceManager->getTexture("Assets/Textures/pipe.png"));

    // bird
    std::shared_ptr<gge::obj::Bird> bird = std::make_shared<gge::obj::Bird>();
    level->physicsManager.addNewBody(std::static_pointer_cast<gge::obj::KinematicBody>(bird));
    level->addChild(bird);
    bird->setRectPixelSize(24, 16);
    bird->setCurrentPos( (sf::Vector2f(gge::GAME_WIDTH, gge::GAME_HEIGHT) - bird->getRect().getSize()) / 2.f );
    // sprite
    std::shared_ptr<gge::obj::Sprite> birdSprite = std::make_shared<gge::obj::Sprite>();
    bird->addChild(birdSprite);
    level->drawablesManager.newDrawable(birdSprite, 0, 0);
    birdSprite->setTexture(resourceManager->getTexture("Assets/Textures/bird.png"));
}