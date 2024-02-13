#include "GGE/Level.hpp"

using gge::Level;

// Init level
void Level::init(){
    // create layers of drawables
    const int layersCount = 10;
    for(int i = 0; i < layersCount; ++i){
        levelDrawableLayers.push_back(std::vector<std::weak_ptr<obj::Drawable>>());
        guiDrawableLayers.push_back(std::vector<std::weak_ptr<obj::Drawable>>());
    }

    // init gui view
    guiView.setSize(GAME_WIDTH, GAME_HEIGHT);
    guiView.setCenter(GAME_WIDTH/2, GAME_HEIGHT/2);
};