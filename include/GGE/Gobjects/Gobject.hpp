#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

// 4 directions
enum class Direction {
    None, Up, Down, Right, Left
};

namespace gge::obj {

// Gobject class
class Gobject : public std::enable_shared_from_this<Gobject>
{
private:
    // Variables
    sf::Vector2f relativePos;
    sf::FloatRect selfRect;
    bool flipped;

protected:
    // Variables
    std::vector<std::shared_ptr<Gobject>> children;
    bool doesFlipMirror;

    // Methods
    // update everything related to position
    virtual void updatePos(); 

public:
    // Structors
    Gobject();
    ~Gobject();

    // Variables
    std::weak_ptr<Gobject> parentWeak;

    // Methods
    // Update the state of the object
    virtual void update(const float& dTimeMs);
    
    // Set position relative to parent's position
    void setRelativePos(const sf::Vector2f& newPos);
    // move self by some distance
    void move(const sf::Vector2f& distance);
    
    // Add a new child
    void addChild(std::shared_ptr<Gobject> newChild);
    // Remove a child
    void removeChild(std::shared_ptr<Gobject> child);
    // Remove self
    void removeSelf();
    
    // set rect size
    virtual void setRectSize(const sf::Vector2f& newSize);
    // set rect pixel-scaled size
    void setRectPixelSize(float w, float h);

    // set the flip of the object
    virtual void setFlip(bool newFlip);
    // set doesFlipMirror to true
    void makeFlippable();
    
    // Getters
    // Get position relative to parent's position
    const sf::Vector2f& getRelativePos();
    // Get collider
    const sf::FloatRect& getRect();
    // get flipped
    const bool& isFlipped();
};

}