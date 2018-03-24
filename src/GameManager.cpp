#include "GameManager.hpp"

#include <GL/glew.h>

#include "render/Render.hpp"

Scene* GameManager::nextScene = nullptr;
Scene* GameManager::currentScene = nullptr;

void GameManager::runGame(SDL_Window* window)
{
    bool running = true;

    SDL_Event e;

    Render::initOpenGL();

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

        glClear(GL_COLOR_BUFFER_BIT);

        currentScene->update();
        currentScene->render();

        SDL_GL_SwapWindow(window);
    }
}
