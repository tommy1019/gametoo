#ifndef RenderObject_hpp
#define RenderObject_hpp

#include "string"

#include <SDL.h>

class RenderObject
{
private:
    SDL_Rect clip;
    SDL_Rect renderPos;

    SDL_Texture* texture;
public:
    RenderObject(std::string path, int sx, int sy);
    ~RenderObject();

    void render(SDL_Renderer* renderer);

    void setClip(int x, int y);
    void setPos(int x, int y, int w, int h);
};

#endif
