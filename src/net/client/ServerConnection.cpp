#include "ServerConnection.hpp"

#include <iostream>

#include "../ConnectionManager.hpp"

#include "../../GameManager.hpp"
#include "../../render/scene/GameScene.hpp"

#include "../../event/CreateUnitEvent.hpp"
#include "../../event/UpdateStateEvent.hpp"

TCPsocket ServerConnection::socket;
GameState* ServerConnection::gameState;

SDL_sem* ServerConnection::socketWriteLock;

bool ServerConnection::running = true;

int ServerConnection::connectToServer(void* data)
{
    IPaddress ip;

    socketWriteLock = SDL_CreateSemaphore(1);

    if (SDLNet_ResolveHost(&ip, "localhost", 4668) == -1)
    {
        std::cout << "[Client] Failed to resolve host" << std::endl;
        std::cout << SDLNet_GetError() << std::endl;
        return -1;
    }

    std::cout << "[Client] Trying to connect to the server" << std::endl;
    socket = SDLNet_TCP_Open(&ip);
    if(!socket)
    {
        std::cout << "[Client] Failed to create socket" << std::endl;
        std::cout << SDLNet_GetError() << std::endl;
        return -1;
    }

    std::cout << "[Client] Connected to server" << std::endl;

    gameState = new GameState;
    GameManager::nextScene = new GameScene(gameState);

    while (running)
    {
        uint32_t packetId;
        uint64_t dataSize;

        SDLNet_TCP_Recv(socket, &packetId, sizeof(packetId));
        SDLNet_TCP_Recv(socket, &dataSize, sizeof(dataSize));

        uint8_t* data = new uint8_t[dataSize];
        SDLNet_TCP_Recv(socket, data, static_cast<int>(dataSize));

        switch(packetId)
        {
        case 1:
            {
                Packet* p = new Packet;
                p->packetId = packetId;
                p->dataSize = dataSize;
                p->data = data;

                SDL_SemWait(ConnectionManager::dataLock);
                ConnectionManager::unprocessedPackets.push_back(p);
                SDL_SemPost(ConnectionManager::dataLock);
            }
            break;
        case 2:
            {
                gameState->update();
            }
            break;
        }
    }

    return 0;
}

void ServerConnection::sendDataToServer(uint32_t packetId, uint64_t dataSize, void* data)
{
    SDL_SemWait(socketWriteLock);
    SDLNet_TCP_Send(socket, &packetId, sizeof(packetId));
    SDLNet_TCP_Send(socket, &dataSize, sizeof(dataSize));
    SDLNet_TCP_Send(socket, data, static_cast<int>(dataSize));
    SDL_SemPost(socketWriteLock);
}
