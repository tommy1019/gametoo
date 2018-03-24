#ifndef Chunk_hpp
#define Chunk_hpp

#include <GL/glew.h>

#include "render/RenderObject.hpp"

class Chunk
{
private:
    static GLuint texture;

    int data[64][64];
public:
    static void loadTextures();

    Chunk();

    void render();
};

#endif
