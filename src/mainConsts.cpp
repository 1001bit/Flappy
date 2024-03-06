#include "GGE/Physics/PhysicsManager.hpp"
#include "GGE/Gobjects/Sprite.hpp"

// Sprite
using gge::obj::Sprite;

const float gge::obj::Sprite::SPRITE_SCALE = 4;

// Physics
using gge::PhysicsManager;

const ushort PhysicsManager::UPDATE_RATE = 40;
const float PhysicsManager::GFORCE = 0.052;
const float PhysicsManager::PhysicsManager::AIR_FRICTION = 0.015;
const float PhysicsManager::GROUND_FRICTION = 0.3;
const float PhysicsManager::ACCEL_COEFF = 0.1;