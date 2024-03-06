#pragma once

#include "GGE/Gobjects/KinematicBody.hpp"
#include "GGE/Gobjects/Sprite.hpp"
#include "GGE/Level/Level.hpp"

namespace gge {

class PipesManager : public obj::Gobject
{
private:
    static const float PIPES_SPEED;
    static const float PIPE_SPAWN_RATE;
    static const u_short GAP_SIZE_MIN;
    static const u_short GAP_SIZE_RANDOM;
    static const u_short GAP_OFFSET_RANDOM;

    std::vector<std::weak_ptr<obj::KinematicBody>> pipes;
    std::shared_ptr<Cooldown> pipeSpawnCooldown;
    std::weak_ptr<Level> levelWeak;
    
public:
    bool active;

    // Structors
    PipesManager(std::shared_ptr<Level> level);
    ~PipesManager();

    // Methods
    // Create top and bottom pipes
    void createNewPipePair();
    // Update
    void update(const float& dTimeMs);
    // init cooldowns
    void initCooldowns(CooldownsManager& cooldownsManager);

    // Getters
    // pipes
    const std::vector<std::weak_ptr<obj::KinematicBody>>& getPipes();
};

}