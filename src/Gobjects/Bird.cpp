#include "Gobjects/Bird.hpp"
#include <cmath>

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
    
    spriteWeak = newSprite;
}

// control the player
void Bird::control(){
    gge::ControlsManager* controlsManager = gge::ControlsManager::getInstance();

    // jump
    if(controlsManager->isPressed("jump", true)){
        setVelocity({getVelocity().x, 0});
        addAcceleration({0, -JUMP_FORCE});
    }
}

// rotate the sprite and limit velocity
void Bird::update(const float& dTimeMs){
    auto sprite = spriteWeak.lock();
    if(!sprite){
        return;
    }

    // Rotation
    sprite->sprite.setRotation(0);
}