#include "GGE/Gobjects/View.hpp"

using gge::obj::View;

// Structors
View::View(){}
View::~View(){}

// Methods
// update gobject and view pos
void View::updatePos(){
    Gobject::updatePos();
    view.setCenter(getRect().getPosition() + getRect().getSize()/2.f);
}

// set rect and view size
void View::setRectSize(const sf::Vector2f& size){
    Gobject::setRectSize(size);
    view.setSize(size);
    updatePos();
}

// Getters
// view
const sf::View& View::getView(){
    return view;
}