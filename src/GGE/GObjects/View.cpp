#include "GGE/GObjects/View.hpp"

using gge::obj::View;

// Structors
View::View(){}
View::~View(){}

// Methods
// update gobject and view pos
void View::updatePos(){
    GObject::updatePos();
    view.setCenter(getRect().getPosition() + getRect().getSize()/2.f);
}

// set rect and view size
void View::setRectSize(float w, float h){
    GObject::setRectSize(w, h);
    view.setSize(w, h);
}

// Getters
// view
const sf::View& View::getView(){
    return view;
}