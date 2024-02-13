#pragma once

// #define SHOW_FPS
#define SHOW_FPS_SPIKES

namespace gge {

// Scale of every sprite
constexpr float SPRITE_SCALE = 7;

// Framerate limits
constexpr unsigned MAX_FPS = 150;
constexpr unsigned MIN_FPS = 120;
constexpr unsigned UPDATE_RATE = 60;

// sizes of the game
constexpr unsigned GAME_WIDTH = 1440;
constexpr unsigned GAME_HEIGHT = 880;

}