#include "GGE/Level.hpp"

using gge::Level;

// Structors
Level::Level(){}

Level::~Level(){}

// Init the level
void Level::init(){
    // init gui view
    std::shared_ptr<obj::View> guiView = std::make_shared<obj::View>();
    addChild(guiView);
    guiView->setRectSize({GAME_WIDTH, GAME_HEIGHT});
    guiViewWeak = guiView;

    // init level view
    std::shared_ptr<obj::View> levelView = std::make_shared<obj::View>();
    addChild(levelView);
    levelView->setRectSize({GAME_WIDTH, GAME_HEIGHT});
    levelViewWeak = levelView;

    // drawables manager
    drawablesManager.setLayerCount(10);
}