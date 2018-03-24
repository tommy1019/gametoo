#include "ServerConnection.hpp"

#include <iostream>

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

    if (SDLNet_ResolveHost(&ip, "192.168.1.201", 4668) == -1)
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
        SDLNet_TCP_Recv(socket, data, dataSize);

        switch(packetId)
        {
        case 1:
            {
                CreateUnitEvent* createUnitEvent = (CreateUnitEvent*)data;
                gameState->units.push_back(new Unit(createUnitEvent->x, createUnitEvent->y));
            }
            break;
        case 2:
            {
                gameState->update();
            }
            break;
        }

        delete[] data;
    }

    return 0;
}

void ServerConnection::sendDataToServer(uint32_t packetId, void* data)
{
    uint64_t dataSize = sizeof(data);

    SDL_SemWait(socketWriteLock);
    SDLNet_TCP_Send(socket, &packetId, sizeof(packetId));
    SDLNet_TCP_Send(socket, &dataSize, sizeof(dataSize));
    SDLNet_TCP_Send(socket, data, dataSize);
    SDL_SemPost(socketWriteLock);
}
