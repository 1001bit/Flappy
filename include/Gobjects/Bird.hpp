#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"
#include "GGE/Controls/ControlsManager.hpp"
#include "GGE/Level/Level.hpp"
#include "GGE/Gobjects/Sprite.hpp"

namespace gge::obj {

class Bird : public KinematicBody
{
private:
    std::weak_ptr<Sprite> spriteWeak;

public:
    // Structors
    Bird();
    ~Bird();

    // Methods
    // init everything
    void init(std::shared_ptr<Level> level);
    // Control player
    void control();
    // rotate the sprite
    void update(const float& dTimeMs);
};

}
