#include "ServerConnection.hpp"

#include <iostream>

#include "../../GameState.hpp"

int ServerConnection::connectToServer(void* data)
{
    GameState* gameState = (GameState*)data;

    IPaddress ip;
    TCPsocket socket;

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

    return 0;
}
