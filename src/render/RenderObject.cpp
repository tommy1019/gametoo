#include "RenderObject.hpp"

#include "ResourceManager.hpp"

RenderObject::RenderObject(std::string path, int sx, int sy)
{
    clip.x = sx * 32;
    clip.y = sy * 32;
    clip.w = 32;
    clip.h = 32;

    texture = ResourceManager::loadTexture(path);
}

RenderObject::~RenderObject()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

void RenderObject::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, &clip, &renderPos);
}

void RenderObject::setClip(int x, int y)
{
    clip.x = x * 32;
    clip.y = y * 32;
}

void RenderObject::setPos(int x, int y, int w, int h)
{
    renderPos.x = x;
    renderPos.y = y;
    renderPos.w = w;
    renderPos.h = h;
}
