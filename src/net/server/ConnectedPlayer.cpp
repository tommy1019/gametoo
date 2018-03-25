#include "ConnectedPlayer.hpp"

#include <iostream>

#include "GameServer.hpp"
#include "SyncManager.hpp"

#include "../../event/CreateUnitEvent.hpp"

int ConnectedPlayer::newPlayerId = 0;

int ConnectedPlayer::startThread(void* obj)
{
    ((ConnectedPlayer*)obj)->run();
    return 0;
}

ConnectedPlayer::ConnectedPlayer(TCPsocket socket)
{
    this->socket = socket;
    this->socketWriteLock = SDL_CreateSemaphore(1);

    playerId = newPlayerId++;
}

ConnectedPlayer::~ConnectedPlayer()
{
    SDL_DestroySemaphore(socketWriteLock);
    SDLNet_TCP_Close(socket);
}

void ConnectedPlayer::run()
{
    while (GameServer::running)
    {
        uint32_t packetId;
        uint64_t dataSize;

        SDLNet_TCP_Recv(socket, &packetId, sizeof(packetId));
        SDLNet_TCP_Recv(socket, &dataSize, sizeof(dataSize));

        uint8_t* data = new uint8_t[dataSize];
        SDLNet_TCP_Recv(socket, data, static_cast<int>(dataSize));

        SDL_SemWait(SyncManager::dataLock);

        switch (packetId)
        {
            case 1:
            {
                CreateUnitEvent* e = (CreateUnitEvent*)(data);
                Unit* u = new Unit(e->x, e->y);
                GameServer::gameState.units.push_back(u);
                GameServer::broadcastData(packetId, sizeof(CreateUnitEvent), data);
            }
                break;
            default:
            {
                std::cout << "[Server] Unknown packet id: " << packetId << std::endl;
            }
                break;
        }

        SDL_SemPost(SyncManager::dataLock);

        delete[] data;
    }
}

void ConnectedPlayer::sendData(uint32_t packetId, uint64_t dataSize, void* data)
{
    SDL_SemWait(socketWriteLock);
    SDLNet_TCP_Send(socket, &packetId, sizeof(packetId));
    SDLNet_TCP_Send(socket, &dataSize, sizeof(dataSize));
    SDLNet_TCP_Send(socket, data, static_cast<int>(dataSize));
    SDL_SemPost(socketWriteLock);
}
