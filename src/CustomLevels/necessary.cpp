#include "inits.hpp"

using namespace gge;

void clvl::necessaryInit(std::shared_ptr<Level> level){
    ResourceManager* resourceManager = ResourceManager::getInstance();

    // Level
    // camera
    level->camera = std::make_shared<obj::Camera>();
    level->camera->setRectSize(GAME_WIDTH, GAME_HEIGHT);
    level->updatableGObjects.push_back(level->camera);

    // Gui
    // Dialogue box
    std::shared_ptr<obj::Sprite> dialogueBox = std::make_shared<obj::Sprite>();
    dialogueBox->setNewParent(level);
    level->guiDrawableLayers[0].push_back(dialogueBox);
    
    // Dialogue text
    std::shared_ptr<obj::Text> dialogueText = std::make_shared<obj::Text>();
    dialogueText->setNewParent(dialogueBox);
    level->guiDrawableLayers[1].push_back(dialogueText);

    level->dialogueManager.initDrawables(dialogueBox, dialogueText);
}