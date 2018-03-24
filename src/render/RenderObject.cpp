#include "RenderObject.hpp"

#include <iostream>

#include "ResourceManager.hpp"

RenderObject::RenderObject(std::string path, int sx, int sy)
{
    texture = ResourceManager::loadTexture(path);
}

RenderObject::~RenderObject()
{
    std::cout << "Still not unloading textures..." << std::endl;
}

void RenderObject::render()
{
    
}

void RenderObject::setClip(int x, int y)
{

}

void RenderObject::setPos(int x, int y, int w, int h)
{

}
