#include "GameServer.hpp"

#include <iostream>

#include "SyncManager.hpp"

#include "../../event/CreateUnitEvent.hpp"

std::vector<ConnectedPlayer*> GameServer::connectedPlayers;
std::vector<SDL_Thread*> GameServer::connectedPlayerThreads;

bool GameServer::running = true;
int GameServer::numConnected = 0;

SDL_Thread* GameServer::syncThread;

GameState GameServer::gameState;

int GameServer::startAcceptionConnections(void* data)
{
    std::cout << "[Server] Initialization..." << std::endl;

    TCPsocket serverSocket;
    IPaddress listenAddress;
    if (SDLNet_ResolveHost(&listenAddress, "0.0.0.0", 4668) == -1)
    {
        std::cout << "[Server] Failed to get host address" << std::endl;
        std::cout << SDLNet_GetError() << std::endl;
    }

    serverSocket = SDLNet_TCP_Open(&listenAddress);
    if(!serverSocket)
    {
        std::cout << "[Server] Failed to open server socket" << std::endl;
        std::cout << SDLNet_GetError() << std::endl;

        return -1;
    }

    syncThread = SDL_CreateThread(SyncManager::run, "ServerSyncThread", nullptr);

    while (running)
    {
        TCPsocket newConnection;

        newConnection = SDLNet_TCP_Accept(serverSocket);

        if (!newConnection)
        {
            SDL_Delay(500);
            continue;
        }

        SDL_SemWait(SyncManager::dataLock);

        ConnectedPlayer* newPlayer = new ConnectedPlayer(newConnection);
        connectedPlayers.push_back(newPlayer);

        for (Unit* u : gameState.units)
        {
            CreateUnitEvent e;
            e.x = u->x;
            e.y = u->y;
            newPlayer->sendData(1, sizeof(CreateUnitEvent), &e);
        }

        numConnected++;

        SDL_Thread* playerThread;
        SDL_CreateThread(ConnectedPlayer::startThread, "ConnectedPlayerThread", (void*)(newPlayer));
        connectedPlayerThreads.push_back(playerThread);

        SDL_SemPost(SyncManager::dataLock);

        std::cout << "[Server] Received connection" << std::endl;
    }

    return 0;
}

void GameServer::broadcastData(uint32_t packetId, uint64_t dataSize, void* data)
{
    for (ConnectedPlayer* p : connectedPlayers)
        p->sendData(packetId, dataSize, data);
}
