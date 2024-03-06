#pragma once

#include "GGE/Gobjects/Text.hpp"
#include "GGE/Gobjects/KinematicBody.hpp"
#include "Pipes/PipesManager.hpp"

namespace gge {

class Score : public obj::Gobject
{
private:
    std::weak_ptr<PipesManager> pipesManagerWeak;
    std::weak_ptr<obj::KinematicBody> birdWeak;
    std::weak_ptr<obj::Text> textWeak;
    unsigned score;

public:
    // Structors
    Score(std::shared_ptr<PipesManager> pipesManager, std::shared_ptr<obj::KinematicBody> bird);
    ~Score();

    // Methods
    // init text
    void init(std::shared_ptr<Level> level);
    // check for bird-pipe collision
    void update(const float& dTimeMs);
};

}