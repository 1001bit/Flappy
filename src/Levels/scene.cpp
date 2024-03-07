#include "inits.hpp"

#include "Gobjects/Bird.hpp"
#include "Background/BackgroundManager.hpp"
#include "Pipes/PipesManager.hpp"
#include "Instructions/AcRestart.hpp"
#include "Instructions/TrCollision.hpp"
#include "Score/Score.hpp"
#include "Instructions/AcStop.hpp"

std::shared_ptr<gge::Level> clvl::newScene(){
    std::shared_ptr<gge::Level> level = std::make_shared<gge::Level>();
    level->init(480, 720);

    // background
    std::shared_ptr<gge::BackgroundManager> backgroundManager = std::make_shared<gge::BackgroundManager>(level);
    level->addChild(backgroundManager);
    level->updatableGobjects.push_back(backgroundManager);
    backgroundManager->init();

    // pipes
    std::shared_ptr<gge::PipesManager> pipesManager = std::make_shared<gge::PipesManager>(level);
    level->addChild(pipesManager);
    level->updatableGobjects.push_back(pipesManager);
    pipesManager->initCooldowns(level->cooldownsManager);

    // bird
    std::shared_ptr<gge::obj::Bird> bird = std::make_shared<gge::obj::Bird>();
    level->physicsManager.addNewBody(std::static_pointer_cast<gge::obj::KinematicBody>(bird));
    level->addChild(bird);
    level->updatableGobjects.push_back(bird);
    bird->init(level);
    bird->setCurrentPos({100, 100}, true);

    // Score
    std::shared_ptr<gge::Score> score = std::make_shared<gge::Score>(pipesManager, bird);
    level->addChild(score);
    score->init(level);
    level->updatableGobjects.push_back(score);

    // instructions
    // restart action
    std::shared_ptr<gge::ins::AcRestart> restartAction = std::make_shared<gge::ins::AcRestart>(level);
    level->instructionsManager.actionsVector.push_back(restartAction);
    // restart trigger
    std::shared_ptr<gge::ins::TrRestart> restartTrigger = std::make_shared<gge::ins::TrRestart>(bird);
    level->instructionsManager.triggersVector.push_back(restartTrigger);
    restartTrigger->setActive(false);
    restartTrigger->addAction(restartAction);

    // stop action
    std::shared_ptr<gge::ins::AcStop> stopAction = std::make_shared<gge::ins::AcStop>(bird, pipesManager, backgroundManager, restartTrigger);
    level->instructionsManager.actionsVector.push_back(stopAction);
    // collision trigger
    std::shared_ptr<gge::ins::TrCollision> collisionTrigger = std::make_shared<gge::ins::TrCollision>(pipesManager, bird, level);
    level->instructionsManager.triggersVector.push_back(collisionTrigger);
    collisionTrigger->addAction(stopAction);

    return level;
}