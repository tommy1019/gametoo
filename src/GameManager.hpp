#ifndef GameManager_hpp
#define GameManager_hpp

#include <SDL.h>

#include "render/scene/Scene.hpp"

class GameManager
{
private:
    static Scene* currentScene;

public:
    static SDL_Renderer* renderer;

    static Scene* nextScene;

    static void runGame(SDL_Renderer* renderer);
};

#endif
