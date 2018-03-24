#ifndef Chunk_hpp
#define Chunk_hpp

#include <SDL.h>

#include "render/RenderObject.hpp"

class Chunk
{
private:
    static SDL_Texture* texture;

    int data[64][64];
public:
    static void loadTextures();

    Chunk();

    void render(SDL_Renderer* renderer);
};

#endif
