#include "Gobjects/Bird.hpp"

using gge::obj::Bird;

const float Bird::JUMP_FORCE = 9;

// Structors
Bird::Bird(){
    applyGravity = true;
    applyCollisions = true;
    applyControl = true;
    maxVelocity = 50;
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
    level->drawablesManager.newDrawable(newSprite, false, 2);
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
void Bird::update(const float&){
    auto sprite = spriteWeak.lock();
    if(!sprite){
        return;
    }

    // Rotation
    float rotRange = 120;
    float normalizedVelY = (getVelocity().y + maxVelocity) / (2 * maxVelocity);
    float targetRot = (rotRange / -2) + normalizedVelY * rotRange;

    sprite->sprite.setRotation(targetRot);
}

// make bird fall
void Bird::kill(){
    applyControl = false;
}