#include "GGECustom/Background/BackgroundManager.hpp"
#include "GGECustom/GameConstants.hpp"
#include <cmath>

constexpr float BACKGROUND_SPEED = 0.5;

using gge::BackgroundManager;

// Structors
BackgroundManager::BackgroundManager(){}
BackgroundManager::~BackgroundManager(){}

// Methods
// make baseBackgroundSprite
void BackgroundManager::initBackgroundSprite(){
    auto level = levelWeak.lock();
    if(!level){
        return;
    }

    backgroundSpriteBase.setTexture(level->resourceManager.getTexture("Assets/Textures/background.png"));

    // make as many backgrounds as needed depending on game size / background size ratio
    backgrounds.clear();
    for(ushort i = 0; i < ceil(GAME_WIDTH / backgroundSpriteBase.getRect().width) + 1; ++i){ // add extra one for stability
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
    background->setRectSize(backgroundSpriteBase.getRect().getSize());
    background->accelerate(-BACKGROUND_SPEED, 0);

    // place it right after previous background
    if(backgrounds.size()){
        if(auto lastBackground = backgrounds.back().lock()){
            background->setCurrentPos({lastBackground->getCurrentRect().left + lastBackground->getCurrentRect().width, 0}, true);
        }
    }
    backgrounds.push_back(background);

    // sprite
    std::shared_ptr sprite = std::make_shared<obj::Sprite>(backgroundSpriteBase);
    background->addChild(sprite);
    level->drawablesManager.newDrawable(sprite, false, 0);
}

// Update
void BackgroundManager::update(const float& dTimeMs){
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