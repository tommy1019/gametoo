#include "ConnectedPlayer.hpp"

#include <iostream>

#include "GameServer.hpp"
#include "SyncManager.hpp"

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
        SDLNet_TCP_Recv(socket, data, dataSize);

        if (packetId == 2)
        {
            SyncManager::handelClientInput(playerId);
        }
        else
        {
            GameServer::broadcastData(packetId, data);
        }

        delete[] data;
    }
}

void ConnectedPlayer::sendData(uint32_t packetId, void *data)
{
    uint64_t dataSize = sizeof(data);

    SDL_SemWait(socketWriteLock);
    SDLNet_TCP_Send(socket, &packetId, sizeof(packetId));
    SDLNet_TCP_Send(socket, &dataSize, sizeof(dataSize));
    SDLNet_TCP_Send(socket, data, dataSize);
    SDL_SemPost(socketWriteLock);
}
