#include "GameServer.hpp"

#include <iostream>

#include "../../UpdateStateEvent.hpp"

std::vector<ConnectedPlayer*> GameServer::connectedPlayers;
std::vector<SDL_Thread*> GameServer::connectedPlayerThreads;

SDL_sem* GameServer::setLock;
std::unordered_set<int> GameServer::respondedPlayers;

int GameServer::numConnected = 0;
int GameServer::inputsReceived = 0;

bool GameServer::running = true;

int GameServer::startAcceptionConnections(void* data)
{
    std::cout << "[Server] Initialization..." << std::endl;

    setLock = SDL_CreateSemaphore(1);

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
            SDL_Delay(500);
            //std::cout << "Error on accept." << std::endl;
            //std::cout << SDLNet_GetError() << std::endl;
            continue;
        }

        ConnectedPlayer* newPlayer = new ConnectedPlayer(newConnection);
        connectedPlayers.push_back(newPlayer);

        numConnected++;

        SDL_Thread* playerThread;
        SDL_CreateThread(ConnectedPlayer::startThread, "ConnectedPlayerThread", (void*)(newPlayer));
        connectedPlayerThreads.push_back(playerThread);

        std::cout << "[Server] Received connection" << std::endl;
    }

    return 0;
}

void GameServer::broadcastData(uint32_t packetId, void *data)
{
    for (ConnectedPlayer* p : connectedPlayers)
        p->sendData(packetId, data);
}

void GameServer::onInput(int playerId)
{
    SDL_SemWait(setLock);

    if (respondedPlayers.count(playerId) > 0)
        return;

    inputsReceived++;
    respondedPlayers.insert(playerId);

    if (inputsReceived >= numConnected)
    {
        inputsReceived = 0;
        respondedPlayers.clear();

        UpdateStateEvent e;
        e.stepNum = 1;

        broadcastData(2, &e);
    }

    SDL_SemPost(setLock);
}
