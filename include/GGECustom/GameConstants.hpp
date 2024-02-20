#pragma once

// #define SHOW_FPS
#define SHOW_FPS_SPIKES

namespace gge {

// Scale of every sprite
constexpr float SPRITE_SCALE = 4;

// Framerate limits
constexpr unsigned MAX_FPS = 150;
constexpr unsigned MIN_FPS = 120;
constexpr unsigned UPDATE_RATE = 60;

// size of the game view
constexpr unsigned GAME_WIDTH = 480;
constexpr unsigned GAME_HEIGHT = 720;

// Physics
constexpr float GFORCE = 0.052;
constexpr float AIR_FRICTION = 0.015;
constexpr float GROUND_FRICTION = 0.3;
constexpr float ACCEL_COEFF = 0.1;

}