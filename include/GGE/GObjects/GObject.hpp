#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "GGE/Cooldowns/CooldownsManager.hpp"
#include "GGE/GameConstants.hpp"

// 4 directions
enum class Direction {
    None, Up, Down, Right, Left
};

namespace gge::obj {

// GObject class
class GObject : public std::enable_shared_from_this<GObject>
{
private:
    // Variables
    sf::Vector2f relativePos;
    sf::FloatRect selfRect;
    bool flipped;

protected:
    // Variables
    std::weak_ptr<GObject> parentWeak;
    std::vector<std::shared_ptr<GObject>> children;
    std::unordered_map<std::string, std::shared_ptr<Cooldown>> selfCooldownMap;
    bool doesFlipMirror;

    // Methods
    // set self rect relative position and children's position
    virtual void updatePos(); 

public:
    // Structors
    GObject();
    ~GObject();

    // Methods
    // Update the state of the object
    virtual void update(const float& dTimeMs);
    
    // Set position relative to parent's position
    void setRelativePos(const sf::Vector2f& newPos);
    // move self by some distance
    void move(const sf::Vector2f& distance);

    // Set a parent
    void setNewParent(std::shared_ptr<GObject> newParent);
    // Add a new child
    void addChild(std::shared_ptr<GObject> newChild);
    // Remove a child
    void removeChild(std::shared_ptr<GObject> child);
    
    // set rect pixel size
    virtual void setRectSize(float w, float h);
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