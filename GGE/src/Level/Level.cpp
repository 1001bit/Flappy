#include "GGE/Level/Level.hpp"

using gge::Level;

// Structors
Level::Level(){
    pause();
    restartLevel = false;
}

Level::~Level(){}

// Methods
// Init the level
void Level::init(float viewW, float viewH){
    // init gui view
    std::shared_ptr<obj::View> guiView = std::make_shared<obj::View>();
    addChild(guiView);
    guiView->setRectSize({viewW, viewH});
    guiViewWeak = guiView;

    // init level view
    std::shared_ptr<obj::View> levelView = std::make_shared<obj::View>();
    addChild(levelView);
    levelView->setRectSize({viewW, viewH});
    levelViewWeak = levelView;

    // drawables manager
    drawablesManager.setLayerCount(10);

    // is active on start
    resume();
}

// active = true
void Level::resume(){
    active = true;
    cooldownsManager.resumeCooldowns();
}

// active = false
void Level::pause(){
    active = false;
    cooldownsManager.pauseCooldowns();
}

// restartLevel = true
void Level::restart(){
    restartLevel = true;
}

// Getters
// restartLevel
bool Level::doRestart(){
    return restartLevel;
}
// active
bool Level::isActive(){
    return active;
}
// levelView.getSize()
sf::Vector2f Level::getViewSize(){
    if(auto levelView = levelViewWeak.lock()){
        return levelView->getRect().getSize();
    }
    return {0, 0};
}