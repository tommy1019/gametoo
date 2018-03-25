#ifndef Chunk_hpp
#define Chunk_hpp

#include <GL/glew.h>

#include "render/RenderObject.hpp"

class Chunk
{
private:
    static GLuint texture;
    static GLuint tbo[4];

    int data[64][64];

    float mvp[4][4];

public:
    static void loadTextures();

    const double x;
    const double y;

    Chunk(double baseX, double baseY);

    void render();
};

#endif
