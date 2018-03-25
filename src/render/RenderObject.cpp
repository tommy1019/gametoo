#include "RenderObject.hpp"

#include <iostream>

#include "Render.hpp"
#include "ResourceManager.hpp"

RenderObject::RenderObject(std::string path, int sx, int sy, int sw, int sh, int textSheetSize)
{
    texture = ResourceManager::loadTexture(path);

    float tx = static_cast<double>(sx * sw) / textSheetSize;
    float ty = static_cast<double>(sy * sh) / textSheetSize;

    float tw = static_cast<double>(sw) / textSheetSize;
    float th = static_cast<double>(sh) / textSheetSize;

    GLfloat textureData[] =
    {
        tx, ty + th,
        tx + tw, ty + th,
        tx + tw, ty,
        tx, ty
    };

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            mvp[i][j] = 0;

    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), textureData, GL_STATIC_DRAW);
}

RenderObject::~RenderObject()
{
    std::cout << "Still not unloading textures..." << std::endl;

    ResourceManager::unloadTexture(texture);
    glDeleteBuffers(1, &tbo);
}

void RenderObject::render()
{
    Render::renderQuad(mvp[0], texture, tbo);
}

void RenderObject::setPos(double x, double y, double w, double h)
{
    mvp[0][0] = w;
    mvp[1][1] = h;
    mvp[2][2] = 1;
    mvp[3][3] = 1;
    mvp[3][0] = x;
    mvp[3][1] = y;
}
