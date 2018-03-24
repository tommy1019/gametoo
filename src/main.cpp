#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>

#include <iostream>

#include "GameManager.hpp"
#include "render/scene/SplashScene.hpp"

int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

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

    window = SDL_CreateWindow("GameToo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Error creating SDL window" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "Error initializing SDL_image" << std::endl;
        std::cout << IMG_GetError() << std::endl;
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "Error creating renderer" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    GameManager::renderer = renderer;
    GameManager::nextScene = new SplashScene();
    GameManager::runGame(renderer);

    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
