#ifndef World_hpp
#define World_hpp

#include <vector>
#include <utility>
#include <map>

#include <SDL.h>

#include "Chunk.hpp"

class World
{
public:
    std::vector<Chunk*> chunkList;

	void render(SDL_Renderer* renderer);
};

#endif
