#pragma once

#include "Gobject.hpp"

namespace gge::obj{

class View : public Gobject
{
private:
    sf::View view;

public:
    // Structors
    View();
    ~View();

    // Methods
    // update gobject and view pos
    void updatePos(); 
    // set rect and view size
    void setRectSize(const sf::Vector2f& size);

    // Getters
    // view
    const sf::View& getView();
};

}