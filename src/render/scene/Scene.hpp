#ifndef Scene_hpp
#define Scene_hpp

#include <SDL.h>

class Scene
{
public:
    virtual void render() {};
    virtual void update() {};
    virtual void handelEvent(SDL_Event e) {};

    virtual ~Scene() {};
};

#endif
