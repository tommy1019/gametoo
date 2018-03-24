#include "Chunk.hpp"

#include <iostream>
#include <stdlib.h>

#include "render/ResourceManager.hpp"

SDL_Texture* Chunk::texture;

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

void Chunk::render(SDL_Renderer* renderer)
{
    SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;
    clip.w = 32;
    clip.h = 32;

    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    pos.w = 64;
    pos.h = 64;

    for (int i = 0; i < 64; i++)
        for (int j = 0; j < 64; j++)
        {
            pos.x = i * 64;
            pos.y = j * 64;

            clip.x = (data[i][j] % 16) * 32;
            clip.y = (data[i][j] / 16) * 32;

            SDL_RenderCopy(renderer, texture, &clip, &pos);
        }
}
