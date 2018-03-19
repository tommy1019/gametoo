#include "ConnectionManager.hpp"

#include <iostream>

#include "server/GameServer.hpp"
#include "client/ServerConnection.hpp"

SDL_Thread* ConnectionManager::gameServerThread;
SDL_Thread* ConnectionManager::connectionThread;

void ConnectionManager::startMPServer()
{
    gameServerThread = SDL_CreateThread(GameServer::startAcceptionConnections, "GameServer", nullptr);
}

void ConnectionManager::connectToServer(GameState* clientGameState)
{
    connectionThread = SDL_CreateThread(ServerConnection::connectToServer, "ServerConnection", clientGameState);
}
