#pragma once

#include "GGE/Level.hpp"
#include "GGE/CustomInstructions/AcDialogue.hpp"
#include "GGE/CustomInstructions/TrCollision.hpp"

namespace clvl{
    void necessaryInit(std::shared_ptr<gge::Level> level);
    void testInit(std::shared_ptr<gge::Level> level);
}