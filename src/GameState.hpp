#ifndef GameState_hpp
#define GameState_hpp

#include <vector>

#include "Unit.hpp"

class GameState
{
public:
    std::vector<Unit*> units;
};

#endif
