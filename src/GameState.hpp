#ifndef GameState_hpp
#define GameState_hpp

#include <vector>

#include "World.hpp"
#include "Unit.hpp"

class GameState
{
public:
    std::vector<Unit*> units;
    World* world;

    void update();
};

#endif
