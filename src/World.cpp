#include "World.hpp"

void World::render(SDL_Renderer* renderer)
{
    for (Chunk* c : chunkList)
    {
        c->render(renderer);
    }
}
