#include "Chunk.hpp"

#include <iostream>
#include <stdlib.h>

#include "render/ResourceManager.hpp"

GLuint Chunk::texture;

void Chunk::loadTextures()
{
    texture = ResourceManager::loadTexture("res/terrain.png");
}

Chunk::Chunk()
{
    for (int i = 0; i < 64; i++)
        for (int j = 0; j < 64; j++)
            data[i][j] = rand() % 2;
}

void Chunk::render()
{
    for (int i = 0; i < 64; i++)
        for (int j = 0; j < 64; j++)
        {
            
        }
}
