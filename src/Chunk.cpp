#include "Chunk.hpp"

#include <iostream>
#include <stdlib.h>

#include "render/ResourceManager.hpp"
#include "render/Render.hpp"

GLuint Chunk::texture;
GLuint Chunk::tbo[4];

void Chunk::loadTextures()
{
    texture = ResourceManager::loadTexture("res/terrain.png");


    glGenBuffers(4, tbo);

    for (int i = 0; i < 4; i++)
    {
        float tx = ((i % 16) * 32.0) / 512.0;
        float ty = ((i / 16) * 32.0) / 512.0;

        float tw = 32.0 / 512.0;

        GLfloat textureData[] =
        {
            tx, ty + tw,
            tx + tw, ty + tw,
            tx + tw, ty,
            tx, ty
        };

        glBindBuffer(GL_ARRAY_BUFFER, tbo[i]);
        glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), textureData, GL_STATIC_DRAW);
    }
}

Chunk::Chunk(double baseX, double baseY) : x(baseX), y(baseY)
{
    for (int i = 0; i < 64; i++)
        for (int j = 0; j < 64; j++)
            data[i][j] = rand() % 2;

    mvp[0][0] = 1; mvp[0][1] = 0; mvp[0][2] = 0; mvp[0][3] = 0;
    mvp[1][0] = 0; mvp[1][1] = 1; mvp[1][2] = 0; mvp[1][3] = 0;
    mvp[2][0] = 0; mvp[2][1] = 0; mvp[2][2] = 1; mvp[2][3] = 0;
    mvp[3][0] = baseX; mvp[3][1] = baseY; mvp[3][2] = 0; mvp[3][3] = 1;
}

void Chunk::render()
{
    for (int i = 0; i < 64; i++)
        for (int j = 0; j < 64; j++)
        {
            mvp[3][0] = x + i;
            mvp[3][1] = y + j;
            Render::renderQuad(mvp[0], texture, tbo[data[i][j]]);
        }
}
