#include "SyncManager.hpp"

#include <iostream>

#include "GameServer.hpp"
#include "../../event/UpdateStateEvent.hpp"

SDL_sem* SyncManager::dataLock;

int SyncManager::run(void* data)
{
    dataLock = SDL_CreateSemaphore(1);

    uint32_t now = SDL_GetTicks();
    uint32_t lastUpdate = SDL_GetTicks();

    int updateRate = 60;
    int updateDelta = 1000 / updateRate *  2;

    while (GameServer::running)
    {
        now = SDL_GetTicks();
        uint32_t delta = now - lastUpdate;
        lastUpdate = now;

        if (delta < updateDelta)
            SDL_Delay(updateDelta - delta);

        SDL_SemWait(dataLock);
        UpdateStateEvent e;
        e.stepNum = 0;
        GameServer::broadcastData(2, &e);
        SDL_SemPost(dataLock);
    }

    return 0;
}
