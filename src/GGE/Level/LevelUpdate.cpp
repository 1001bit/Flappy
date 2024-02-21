#include "GGE/Level.hpp"

using gge::Level;

// Methods
// Update everything in the level
void Level::update(const float& dTimeMs){
    for(auto it = updatableGobjects.begin(); it != updatableGobjects.end();){
        auto object = it->lock();
        if(!object){
            it = updatableGobjects.erase(it);
            continue;
        }

        object->update(dTimeMs);

        ++it;
    }
};