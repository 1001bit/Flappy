#include "GGE/Gobjects/Sprite.hpp"

using gge::obj::Sprite;

// Structors
Sprite::Sprite(){
    sprite.setScale(SPRITE_SCALE, SPRITE_SCALE);
}

Sprite::~Sprite(){}

// Methods
// set a texture
void Sprite::setTexture(const sf::Texture& texture){
    sprite.setTexture(texture);
    setRectSize(sprite.getGlobalBounds().getSize());

    // set origin to center
    setOrigin(sprite.getLocalBounds().getSize() / 2.f);
}

// set the flip of the object
void Sprite::setFlip(bool flip){
    if(flip != isFlipped()){
        sprite.scale(-1, 1);
    }

    Gobject::setFlip(flip);
}

// Update sprite and gobject pos
void Sprite::updatePos(){
    Gobject::updatePos();
    // make sprite position independent from origin
    sprite.setPosition(getRect().getPosition() + sprite.getOrigin() * SPRITE_SCALE);
}

// set the origin of the sprite
void Sprite::setOrigin(sf::Vector2f origin){
    sprite.setOrigin(origin);
    updatePos();
}

// draw self drawable object
void Sprite::drawSelf(sf::RenderWindow& window){
    window.draw(sprite);
}