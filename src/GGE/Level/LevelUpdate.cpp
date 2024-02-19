#include "GGE/Level.hpp"

using gge::Level;

// Methods
// Update everything in the level
void Level::update(const float& dTimeMs){
    for(auto it = updatableGObjects.begin(); it != updatableGObjects.end();){
        auto object = it->lock();
        if(!object){
            it = updatableGObjects.erase(it);
            continue;
        }

        object->update(dTimeMs);

        ++it;
    }
};