#include "GGECustom/Dialogues/DialogueManager.hpp"

using gge::DialogueManager;

// Structors
DialogueManager::DialogueManager(){}
DialogueManager::~DialogueManager(){}

// Methods
// Init drawable part
void DialogueManager::initDrawables(std::shared_ptr<obj::Sprite> newDialogueBox, std::shared_ptr<obj::Text> newDialogueText){
    ResourceManager* resourceManager = ResourceManager::getInstance();

    // Dialogue box
    dialogueBoxWeak = newDialogueBox;
    newDialogueBox->setTexture(resourceManager->getTexture("Assets/Textures/dialogueBackground.png"));
    setDrawableVisiblity(0);
    
    // Dialogue text
    dialogueTextWeak = newDialogueText;
    newDialogueText->text.setFont(resourceManager->getFont("Assets/Fonts/font1.ttf"));
    newDialogueText->text.setCharacterSize(30);
    newDialogueText->text.setString("...");
    newDialogueText->setRelativePos({60, 20});
}

// Set all the dialogues list
void DialogueManager::setDialoguesMap(std::unordered_map<u_char, std::shared_ptr<Dialogue>> newDialogues){
    dialoguesMap = newDialogues;
}

// Set current dialogue with id
void DialogueManager::startDialogue(u_char id){
    if(!dialoguesMap.count(id)){
        return;
    }
    setDrawableVisiblity(1);
    currentDialogueWeak = dialoguesMap.at(id);
}

// Update current dialogue
void DialogueManager::updateCurrentDialogue(std::unordered_map<uint16_t, std::weak_ptr<obj::GObject>>& levelGObjectsWId, std::shared_ptr<obj::Camera> camera){
    // if current dialogue is active
    auto currentDialogue = currentDialogueWeak.lock();
    if(!currentDialogue){
        return;
    }

    currentDialogue->update();

    // set dialogue text
    if(auto dialogueText = dialogueTextWeak.lock()){
        dialogueText->text.setString(currentDialogue->getCurrentLine().line);
    }

    // set camera target
    uint16_t speakerId = currentDialogue->getCurrentLine().characterId;
    std::shared_ptr<obj::GObject> currentSpeaker = levelGObjectsWId.at(1).lock();
    if(levelGObjectsWId.count(speakerId)){
        currentSpeaker = levelGObjectsWId.at(speakerId).lock();
        if(!currentSpeaker){
            levelGObjectsWId.erase(speakerId);
            currentSpeaker = levelGObjectsWId.at(1).lock();
        }
    }
    camera->setTarget(currentSpeaker);

    // if empty string (after last line) - stop it
    if(currentDialogue->getCurrentLine().line == ""){
        currentDialogueWeak.reset();
        setDrawableVisiblity(0);
    }
}

// Hide or show drawable part
void DialogueManager::setDrawableVisiblity(bool visible){
    if(auto dialogueBox = dialogueBoxWeak.lock()){
        if(visible){
            dialogueBox->setRelativePos({(GAME_WIDTH-(dialogueBox->sprite.getGlobalBounds().width))/2, 600}); // centralize it on X position
        } else {
            dialogueBox->setRelativePos({9999, 9999});
        }
    }
}