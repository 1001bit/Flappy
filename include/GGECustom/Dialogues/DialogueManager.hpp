#pragma once

#include <unordered_map>
#include "GGECustom/Dialogues/Dialogue.hpp"
#include "GGE/GObjects/Text.hpp"
#include "GGE/GObjects/Sprite.hpp"
#include "GGE/GObjects/Camera.hpp"
#include "GGE/ResourceManager/ResourceManager.hpp"
#include "GGE/GameConstants.hpp"

namespace gge {

class DialogueManager
{
private:
    // Variables
    // all the dialogues and their id's
    std::unordered_map<u_char, std::shared_ptr<Dialogue>> dialoguesMap;
    // current dialogue
    std::weak_ptr<Dialogue> currentDialogueWeak;

    // dialogue box sprite
    std::weak_ptr<obj::Sprite> dialogueBoxWeak;
    // dialogue text inside a box
    std::weak_ptr<obj::Text> dialogueTextWeak;

public:
    // Structors
    DialogueManager();
    ~DialogueManager();

    // Methods
    // Init drawable part
    void initDrawables(std::shared_ptr<obj::Sprite> newDialogueBox, std::shared_ptr<obj::Text> newDialogueText);
    // Set all the dialogues list
    void setDialoguesMap(std::unordered_map<u_char, std::shared_ptr<Dialogue>> newDialogues);

    // Update current dialogue
    void updateCurrentDialogue(std::unordered_map<uint16_t, std::weak_ptr<obj::GObject>>& levelGObjectsWId, std::shared_ptr<obj::Camera> camera);
    // Set current dialogue with id
    void startDialogue(u_char id);
    // Hide or show drawable part
    void setDrawableVisiblity(bool visible);
};

}