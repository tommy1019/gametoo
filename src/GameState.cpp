#include "GameState.hpp"

#include <iostream>

#include <SDL.h>

static uint32_t updates = 0;
static uint32_t startTime = 0;
static uint32_t totalTime = 0;

void GameState::update()
{
    uint32_t curTime = SDL_GetTicks();
    updates++;

    totalTime += (curTime - startTime);

    if (totalTime > 1000)
    {
        std::cout << "[Client] UPS: " << updates << std::endl;
        updates = 0;
        totalTime = 0;
    }

    startTime = curTime;

    //std::cout << "[Client] Updating" << std::endl;
}
