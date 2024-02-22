#include "GGE/Gobjects/Sprite.hpp"

using gge::obj::Sprite;

// Structors
Sprite::Sprite(){
    this->sprite.scale(SPRITE_SCALE, SPRITE_SCALE);
}

Sprite::~Sprite(){}

// Methods
// set a texture
void Sprite::setTexture(const sf::Texture& newTexture){
    sprite.setTexture(newTexture);
    setRectSize(sprite.getGlobalBounds().getSize());
}

// set the flip of the object
void Sprite::setFlip(bool newFlip){
    const int textureWidth = sprite.getTexture()->getSize().x;
    const int textureHeight = sprite.getTexture()->getSize().y;

    if(newFlip){
        sprite.setTextureRect(sf::IntRect(textureWidth, 0, -textureWidth, textureHeight));
    } else {
        sprite.setTextureRect(sf::IntRect(0, 0, textureWidth, textureHeight));
    }

    Gobject::setFlip(newFlip);
};

// Update sprite and gobject pos
void Sprite::updatePos(){
    Gobject::updatePos();
    sprite.setPosition(getRect().getPosition());
} 

// draw self drawable object
void Sprite::drawSelf(sf::RenderWindow& window){
    window.draw(sprite);
};