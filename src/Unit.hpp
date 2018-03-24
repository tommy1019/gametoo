#ifndef Unit_hpp
#define Unit_hpp

#include <SDL.h>

#include "render/RenderObject.hpp"

class Unit
{
private:
    RenderObject render;
public:
    int x, y;

    Unit(int x, int y);

    void draw(SDL_Renderer* renderer);
};

#endif
