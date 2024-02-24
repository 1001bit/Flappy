#include "GGECustom/Pipes/PipesManager.hpp"

constexpr float PIPES_SPEED = 3;
constexpr float PIPE_SPAWN_RATE = 1500;
constexpr u_short GAP_SIZE_MIN = 160;
constexpr u_short GAP_SIZE_RANDOM = 50;
constexpr u_short GAP_OFFSET_RANDOM = 300;

using gge::PipesManager;

// Structors
PipesManager::PipesManager(){
    CooldownsManager* cooldownsManager = CooldownsManager::getInstance();

    moving = true;
    pipeSpawnCooldown = cooldownsManager->newCooldown(Cooldown(PIPE_SPAWN_RATE));
}
PipesManager::~PipesManager(){}

// Methods
void PipesManager::createNewPipePair(){
    auto level = levelWeak.lock();
    if(!level){
        return;
    }

    ResourceManager* resourceManager = ResourceManager::getInstance();

    obj::Sprite sprite;
    sprite.setTexture(resourceManager->getTexture("Assets/Textures/pipe.png"));

    // pipes positioning calculation
    float gap = GAP_SIZE_MIN + rand() % GAP_SIZE_RANDOM;
    float yOffset = -GAP_OFFSET_RANDOM/2.f + rand() % GAP_OFFSET_RANDOM;
    float y1 = GAME_HEIGHT/2.f - sprite.getRect().height + yOffset - gap/2.f;
    float y2 = y1 + gap + sprite.getRect().height;

    // pipe1
    std::shared_ptr<obj::KinematicBody> pipe1 = std::make_shared<obj::KinematicBody>();
    addChild(pipe1);
    level->physicsManager.addNewBody(pipe1);
    pipe1->setRectSize(sprite.getRect().getSize());
    pipe1->setCurrentPos({GAME_WIDTH, y1});
    // sprite
    std::shared_ptr sprite1 = std::make_shared<obj::Sprite>(sprite);
    pipe1->addChild(sprite1);
    level->drawablesManager.newDrawable(sprite1, 0, 1);

    // pipe2
    std::shared_ptr<obj::KinematicBody> pipe2 = std::make_shared<obj::KinematicBody>();
    addChild(pipe2);
    level->physicsManager.addNewBody(pipe2);
    pipe2->setRectSize(sprite.getRect().getSize());
    pipe2->setCurrentPos({GAME_WIDTH, y2});
    // sprite
    std::shared_ptr sprite2 = std::make_shared<obj::Sprite>(sprite);
    pipe2->addChild(sprite2);
    level->drawablesManager.newDrawable(sprite2, 0, 1);

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