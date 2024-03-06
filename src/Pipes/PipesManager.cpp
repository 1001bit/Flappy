#include "Pipes/PipesManager.hpp"

using gge::PipesManager;

const float PipesManager::PIPES_SPEED = 3;
const float PipesManager::PIPE_SPAWN_RATE = 1500;
const u_short PipesManager::GAP_SIZE_MIN = 180;
const u_short PipesManager::GAP_SIZE_RANDOM = 60;
const u_short PipesManager::GAP_OFFSET_RANDOM = 175;

// Structors
PipesManager::PipesManager(std::shared_ptr<Level> level) : 
levelWeak(level)
{
    this->active = true;
}

PipesManager::~PipesManager(){}

// Methods
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

    const sf::Texture& pipeTexture = level->resourceManager.getTexture("Assets/Textures/pipe.png");

    float levelWidth = 0;
    float levelHeight = 0;
    if(auto levelView = level->levelViewWeak.lock()){
        levelWidth = levelView->getRect().width;
        levelHeight = levelView->getRect().height;
    }

    // pipes positioning calculation
    float gap = GAP_SIZE_MIN + rand() % GAP_SIZE_RANDOM; // minGapSize TO minGapSize + random
    float yOffset = -GAP_OFFSET_RANDOM + rand() % GAP_OFFSET_RANDOM*2; // -gapOffset TO gapOffset
    float pipesCenter = levelHeight/2.f + yOffset;
    float y1 = pipesCenter - gap/2.f - pipeTexture.getSize().y * obj::Sprite::SPRITE_SCALE; 
    float y2 = pipesCenter + gap/2.f;

    // pipe
    std::shared_ptr<obj::KinematicBody> pipe = std::make_shared<obj::KinematicBody>();
    addChild(pipe);
    level->physicsManager.addNewBody(pipe);
    pipes.push_back(pipe);
    pipe->setCurrentPos({levelWidth, y1}, true);
    pipe->addAcceleration({-PIPES_SPEED, 0});
    // sprite
    std::shared_ptr sprite = std::make_shared<obj::Sprite>();
    pipe->addChild(sprite);
    level->drawablesManager.newDrawable(sprite, false, 1);
    sprite->setTexture(pipeTexture);
    pipe->setRectSize(sprite->getRect().getSize());

    // pipe
    pipe = std::make_shared<obj::KinematicBody>();
    addChild(pipe);
    level->physicsManager.addNewBody(pipe);
    pipes.push_back(pipe);
    pipe->setCurrentPos({levelWidth, y2}, true);
    pipe->addAcceleration({-PIPES_SPEED, 0});
    // sprite
    sprite = std::make_shared<obj::Sprite>();
    pipe->addChild(sprite);
    level->drawablesManager.newDrawable(sprite, false, 1);
    sprite->setTexture(pipeTexture);
    pipe->setRectSize(sprite->getRect().getSize());
}

// Update
void PipesManager::update(const float&){
    if(!active){
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

// Getters
// pipes
const std::vector<std::weak_ptr<gge::obj::KinematicBody>>& PipesManager::getPipes(){
    return pipes;
}