#include "GGE/Level.hpp"

using gge::Level;

// Structors
Level::Level(){}

Level::~Level(){
    // clear singleton managers on level delete
    ResourceManager* resourceManager = ResourceManager::getInstance();
    CooldownsManager* cooldownsManager = CooldownsManager::getInstance();
    resourceManager->clear();
    cooldownsManager->clear();
}

// Init the level
void Level::init(){
    // init gui view
    std::shared_ptr<obj::View> guiView = std::make_shared<obj::View>();
    addChild(guiView);
    guiView->setRectSize(GAME_WIDTH, GAME_HEIGHT);
    guiView->setRelativePos({0, 0});
    guiViewWeak = guiView;

    // init camera
    std::shared_ptr<obj::SmoothFollower> camera = std::make_shared<obj::SmoothFollower>();
    addChild(camera);
    updatableGObjects.push_back(camera);
    cameraWeak = camera;

    // init level view
    std::shared_ptr<obj::View> levelView = std::make_shared<obj::View>();
    camera->addChild(levelView);
    levelView->setRectSize(GAME_WIDTH, GAME_HEIGHT);
    levelView->setRelativePos(levelView->getRect().getSize() / -2.f);
    levelViewWeak = levelView;

    // drawables manager
    drawablesManager.setLayerCount(10);
}