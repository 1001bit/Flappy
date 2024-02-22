#pragma once

#include "Gobject.hpp"

namespace gge::obj{

class View : public Gobject
{
private:
    sf::View view;
    bool centralized; 

    // Methods
    // set view center to rect center
    void centralize();

public:
    // Structors
    View();
    ~View();

    // Methods
    // update gobject and view pos
    void updatePos(); 
    // set rect and view size
    void setRectSize(const sf::Vector2f& newSize);

    // Getters
    // view
    const sf::View& getView();
};

}