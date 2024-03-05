#include "Gobjects/Bird.hpp"

using gge::obj::Bird;

constexpr float JUMP_FORCE = 9;

// Structors
Bird::Bird(){
    weighs = true;
    collidable = true;
    controllable = true;
}

Bird::~Bird(){}

// Methods
// init everything
void Bird::init(std::shared_ptr<Level> level){
    // rect
    setRectSize(sf::Vector2f(18, 14) * Sprite::SPRITE_SCALE);

    // sprite
    std::shared_ptr<Sprite> newSprite = std::make_shared<Sprite>();
    addChild(newSprite);
    level->drawablesManager.newDrawable(newSprite, false, 1);
    newSprite->setTexture(level->resourceManager.getTexture("Assets/Textures/bird.png"));
    newSprite->setRelativePos((getRect().getSize() - newSprite->getRect().getSize()) / 2.f);
    
    sprite = newSprite;
}

// control the player
void Bird::control(){
    gge::ControlsManager* controlsManager = gge::ControlsManager::getInstance();

    // jump
    if(controlsManager->isPressed("jump", true)){
        velocity.y = 0;
        accelerate(0, -JUMP_FORCE);
    }
}