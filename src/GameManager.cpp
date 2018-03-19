#include "GameManager.hpp"

SDL_Renderer* GameManager::renderer;

Scene* GameManager::nextScene = nullptr;
Scene* GameManager::currentScene = nullptr;

void GameManager::runGame(SDL_Renderer* renderer)
{
    bool running = true;

    SDL_Event e;

    while (running)
    {
        if (nextScene != nullptr)
        {
            delete currentScene;
            currentScene = nextScene;
            nextScene = nullptr;
        }

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }

            currentScene->handelEvent(e);
        }

        SDL_RenderClear(renderer);

        currentScene->update();
        currentScene->render(renderer);

        SDL_RenderPresent(renderer);
    }
}
