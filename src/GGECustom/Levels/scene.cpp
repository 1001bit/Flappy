#include "inits.hpp"

#include "GGECustom/GObjects/Bird.hpp"
#include "GGE/GObjects/Sprite.hpp"

void clvl::scene(std::shared_ptr<gge::Level> level){
    gge::ResourceManager* resourceManager = gge::ResourceManager::getInstance();

    // bird
    std::shared_ptr<gge::obj::Bird> bird = std::make_shared<gge::obj::Bird>();
    level->physicsManager.addNewBody(std::static_pointer_cast<gge::obj::KinematicBody>(bird));
    level->addChild(bird);
    bird->setRectPixelSize(24, 16);
    bird->setCurrentPos(bird->getRect().getSize() / -2.f);
    // sprite
    std::shared_ptr<gge::obj::Sprite> birdSprite = std::make_shared<gge::obj::Sprite>();
    bird->addChild(birdSprite);
    level->drawablesManager.newDrawable(birdSprite, 0, 0);
    birdSprite->setTexture(resourceManager->getTexture("Assets/Textures/bird.png"));
}