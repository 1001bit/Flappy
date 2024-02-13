#include "GGE/GObjects/Text.hpp"

using gge::obj::Text;

// Structors
Text::Text(){}

Text::~Text(){}

// Methods
// Update text and gobject position
void Text::updatePos(){
    GObject::updatePos();

    text.setPosition(getRect().getPosition());
}; 

// draw self text
void Text::drawSelf(sf::RenderWindow& window){
    window.draw(text);
};