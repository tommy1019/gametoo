#include "SyncManager.hpp"

#include <iostream>

#include "GameServer.hpp"
#include "../../UpdateStateEvent.hpp"

SDL_sem* SyncManager::setLock;
std::unordered_set<int> SyncManager::respondedPlayers = std::unordered_set<int>();

std::atomic_int SyncManager::inputsReceived;

int SyncManager::run(void* data)
{
    inputsReceived = 0;

    setLock = SDL_CreateSemaphore(1);

    while (GameServer::running)
    {
        SDL_SemWait(setLock);

        if (inputsReceived >= GameServer::numConnected)
        {
            inputsReceived = 0;
            respondedPlayers.clear();

            UpdateStateEvent e;
            e.stepNum = 1;

            GameServer::broadcastData(2, &e);
        }

        SDL_SemPost(setLock);
    }

    return 0;
}

void SyncManager::handelClientInput(int playerId)
{
    SDL_SemWait(setLock);
    if (respondedPlayers.count(playerId) > 0)
    {
        SDL_SemPost(setLock);
        return;
    }

    inputsReceived++;
    respondedPlayers.insert(playerId);
    SDL_SemPost(setLock);
}
