#pragma once

#include "GObject.hpp"

namespace gge::obj{

class View : public GObject
{
private:
    sf::View view;
    bool centralized; 

public:
    // Structors
    View();
    ~View();

    // Methods
    // update gobject and view pos
    void updatePos(); 
    // set rect and view size
    void setRectSize(float w, float h);

    // Getters
    // view
    const sf::View& getView();
};

}