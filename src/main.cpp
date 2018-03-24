#include <GL/glew.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_net.h>

#include <iostream>

#include "GameManager.hpp"
#include "render/scene/SplashScene.hpp"

int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Error initializing SDL" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }

    if (SDLNet_Init() == -1)
    {
        std::cout << "Error initializing SDL_net" << std::endl;
        std::cout << SDLNet_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("GameToo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
    if (window == nullptr)
    {
        std::cout << "Error creating SDL window" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr)
    {
        std::cout << "Error creating SDL context" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    GLenum status = glewInit();
    if (status != GLEW_OK)
    {
        std::cout << "GLEW failed to initialize!" << std::endl;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "Error initializing SDL_image" << std::endl;
        std::cout << IMG_GetError() << std::endl;
        return -1;
    }

    GameManager::nextScene = new SplashScene();
    GameManager::runGame(window);

    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
