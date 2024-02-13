#pragma once

#include "GGE/Instructions/Action.hpp"
#include "GGE/Dialogues/DialogueManager.hpp"

namespace gge::ins {

class AcDialogue : public Action
{
private:
    // Variables
    u_char dialogueId;
    gge::DialogueManager* dialogueManager;

public:
    // Structors
    AcDialogue();
    ~AcDialogue();

    // Methods
    // set dialogueId, dialogueManager
    void setDialogueParams(u_char newId, gge::DialogueManager* newDialogueManager);
    // start dialogue
    void doAction();
};

}