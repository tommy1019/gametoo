#include "World.hpp"

void World::render()
{
    for (Chunk* c : chunkList)
    {
        c->render();
    }
}
