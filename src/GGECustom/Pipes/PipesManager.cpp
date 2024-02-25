#include "GGECustom/Pipes/PipesManager.hpp"

constexpr float PIPES_SPEED = 3;
constexpr float PIPE_SPAWN_RATE = 1500;
constexpr u_short GAP_SIZE_MIN = 160;
constexpr u_short GAP_SIZE_RANDOM = 50;
constexpr u_short GAP_OFFSET_RANDOM = 175;

using gge::PipesManager;

// Structors
PipesManager::PipesManager(){
    moving = true;
}
PipesManager::~PipesManager(){}

// Methods
// make basePipeSprite
void PipesManager::initPipeSprite(){
    auto level = levelWeak.lock();
    if(!level){
        return;
    }

    pipeSpriteBase.setTexture(level->resourceManager.getTexture("Assets/Textures/pipe.png"));
}

// init cooldowns
void PipesManager::initCooldowns(CooldownsManager& cooldownsManager){
    pipeSpawnCooldown = cooldownsManager.newCooldown(Cooldown(PIPE_SPAWN_RATE));
}

// create a pair of pipes (up and bottom)
void PipesManager::createNewPipePair(){
    auto level = levelWeak.lock();
    if(!level){
        return;
    }

    // pipes positioning calculation
    float gap = GAP_SIZE_MIN + rand() % GAP_SIZE_RANDOM; // minGapSize TO minGapSize + random
    float yOffset = -GAP_OFFSET_RANDOM + rand() % GAP_OFFSET_RANDOM*2; // -gapOffset TO gapOffset
    float pipesCenter = GAME_HEIGHT/2.f + yOffset;
    float y1 = pipesCenter - gap/2.f - pipeSpriteBase.getRect().height; 
    float y2 = pipesCenter + gap/2.f;

    // pipe1
    std::shared_ptr<obj::KinematicBody> pipe1 = std::make_shared<obj::KinematicBody>();
    addChild(pipe1);
    level->physicsManager.addNewBody(pipe1);
    pipe1->setRectSize(pipeSpriteBase.getRect().getSize());
    pipe1->setCurrentPos({GAME_WIDTH, y1});
    // sprite
    std::shared_ptr sprite1 = std::make_shared<obj::Sprite>(pipeSpriteBase);
    pipe1->addChild(sprite1);
    level->drawablesManager.newDrawable(sprite1, false, 1);

    // pipe2
    std::shared_ptr<obj::KinematicBody> pipe2 = std::make_shared<obj::KinematicBody>();
    addChild(pipe2);
    level->physicsManager.addNewBody(pipe2);
    pipe2->setRectSize(pipeSpriteBase.getRect().getSize());
    pipe2->setCurrentPos({GAME_WIDTH, y2});
    // sprite
    std::shared_ptr sprite2 = std::make_shared<obj::Sprite>(pipeSpriteBase);
    pipe2->addChild(sprite2);
    level->drawablesManager.newDrawable(sprite2, false, 1);

    // acceleration
    pipe1->accelerate(-PIPES_SPEED, 0);
    pipe2->accelerate(-PIPES_SPEED, 0);

    // add pipes to pipes vector
    pipes.push_back(pipe1);
    pipes.push_back(pipe2);
}

// Update
void PipesManager::update(const float& dTimeMs){
    if(!moving){
        return;
    }

    // remove pipes when needed
    for(auto it = pipes.begin(); it != pipes.end();){
        auto pipe = it->lock();
        if(!pipe){
            it = pipes.erase(it);
            continue;
        }

        // Remove the pipe if it went outside the screen
        if(pipe->getCurrentRect().left + pipe->getCurrentRect().width < 0){
            it = pipes.erase(it);
            pipe->removeSelf();
            continue;
        }

        ++it;
    }

    // add new pipes when cooldown is over
    if(!pipeSpawnCooldown->getCurrentValueMs()){
        createNewPipePair();
        pipeSpawnCooldown->start();
    }
}