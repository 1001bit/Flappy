#include "Background/BackgroundManager.hpp"
#include <cmath>

using gge::BackgroundManager;

const float BackgroundManager::BACKGROUND_SPEED = 0.5;

// Structors
BackgroundManager::BackgroundManager(std::shared_ptr<Level> level) :
levelWeak(level)
{
    active = true;
}
BackgroundManager::~BackgroundManager(){}

// Methods
// make start bacgrounds
void BackgroundManager::init(){
    auto level = levelWeak.lock();
    if(!level){
        return;
    }

    float backgroundWidth = level->resourceManager.getTexture("Assets/Textures/background.png").getSize().x * obj::Sprite::SPRITE_SCALE;

    // make as many backgrounds as needed depending on game size / background size ratio
    backgrounds.clear();
    for(ushort i = 0; i < ceil(level->getViewSize().x / backgroundWidth) + 1; ++i){ // add extra one for stability
        createNewBackground();
    }
}

// make new background
void BackgroundManager::createNewBackground(){
    auto level = levelWeak.lock();
    if(!level){
        return;
    }

    // background
    std::shared_ptr<obj::KinematicBody> background = std::make_shared<obj::KinematicBody>();
    addChild(background);
    level->physicsManager.addNewBody(background);
    background->addAcceleration({-BACKGROUND_SPEED, 0});

    // place it right after previous background
    if(backgrounds.size()){
        if(auto lastBackground = backgrounds.back().lock()){
            background->setCurrentPos({lastBackground->getCurrentRect().left + lastBackground->getCurrentRect().width, 0}, true);
        }
    }
    backgrounds.push_back(background);

    // sprite
    std::shared_ptr<obj::Sprite> sprite = std::make_shared<obj::Sprite>();
    sprite->setTexture(level->resourceManager.getTexture("Assets/Textures/background.png"));
    background->addChild(sprite);
    background->setRectSize(sprite->getRect().getSize());
    level->drawablesManager.newDrawable(sprite, false, 0);
}

// Update
void BackgroundManager::update(const float&){
    if(!active){
        return;
    }

    auto level = levelWeak.lock();
    if(!level){
        return;
    }

    bool createNew = false;

    // remove backgrounds when needed
    for(auto it = backgrounds.begin(); it != backgrounds.end();){
        auto background = it->lock();
        if(!background){
            it = backgrounds.erase(it);
            continue;
        }

        // Remove the background if it went outside the screen
        if(background->getCurrentRect().left + background->getCurrentRect().width < 0){
            it = backgrounds.erase(it);
            background->removeSelf();
            createNew = true;
            continue;
        }

        ++it;
    }

    // create new background if old went outside
    if(createNew){
        createNewBackground();
    }
}

// stop all background movement
void BackgroundManager::stop(){
    for(auto it = backgrounds.begin(); it != backgrounds.end();){
        auto background = it->lock();
        if(!background){
            it = backgrounds.erase(it);
            continue;
        }

        background->setVelocity({0, 0});

        ++it;
    }
    active = false;
}