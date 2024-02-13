#include "GGECustom/Instructions/AcDialogue.hpp"

using gge::ins::AcDialogue;

// Structors
AcDialogue::AcDialogue(){}
AcDialogue::~AcDialogue(){}

// Methods
// start dialogue
void AcDialogue::doAction(){
    dialogueManager->startDialogue(dialogueId);
}

// set dialogue id and it's manager
void AcDialogue::setDialogueParams(u_char newId, gge::DialogueManager* newDialogueManager){
    dialogueId = newId;
    dialogueManager = newDialogueManager;
}