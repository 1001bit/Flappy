#pragma once

#include "GGE/Level.hpp"
#include "GGECustom/Instructions/AcDialogue.hpp"
#include "GGECustom/Instructions/TrCollision.hpp"

namespace clvl{
    void dialogueInit(std::shared_ptr<gge::Level> level);
    void testInit(std::shared_ptr<gge::Level> level);
}