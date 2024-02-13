#include "inits.hpp"

using namespace gge;

void clvl::dialogueInit(std::shared_ptr<Level> level){
    ResourceManager* resourceManager = ResourceManager::getInstance();

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