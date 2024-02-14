#include "inits.hpp"

#include "GGECustom/GObjects/Bird.hpp"
#include "GGE/GObjects/Sprite.hpp"

void clvl::scene(std::shared_ptr<gge::Level> level){
    gge::ResourceManager* resourceManager = gge::ResourceManager::getInstance();

    // bird
    std::shared_ptr<gge::obj::Bird> bird = std::make_shared<gge::obj::Bird>();
    level->physicsManager.addNewKinematicBody(bird);
    bird->setNewParent(level);
    bird->setRectPixelSize(24, 16);
    // sprite
    std::shared_ptr<gge::obj::Sprite> birdSprite = std::make_shared<gge::obj::Sprite>();
    birdSprite->setNewParent(bird);
    level->levelDrawableLayers[0].push_back(birdSprite);
    birdSprite->setTexture(resourceManager->getTexture("Assets/Textures/bird.png"));
}