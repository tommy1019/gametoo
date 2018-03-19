#include "GameServer.hpp"

#include <iostream>

std::vector<ConnectedPlayer*> GameServer::connectedPlayers;
std::vector<SDL_Thread*> GameServer::connectedPlayerThreads;

bool GameServer::running = true;

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

    while (running)
    {
        TCPsocket newConnection;

        newConnection = SDLNet_TCP_Accept(serverSocket);

        if (!newConnection)
        {
            //std::cout << "Error on accept." << std::endl;
            //std::cout << SDLNet_GetError() << std::endl;
            continue;
        }

        ConnectedPlayer* newPlayer = new ConnectedPlayer(newConnection);
        connectedPlayers.push_back(newPlayer);

        SDL_Thread* playerThread;
        SDL_CreateThread(ConnectedPlayer::startThread, "ConnectedPlayerThread", (void*)(newPlayer));
        connectedPlayerThreads.push_back(playerThread);

        std::cout << "[Server] Received connection" << std::endl;
    }

    return 0;
}
