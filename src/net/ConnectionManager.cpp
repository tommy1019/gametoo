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

void ConnectionManager::connectToServer()
{
    connectionThread = SDL_CreateThread(ServerConnection::connectToServer, "ServerConnection", nullptr);
}

void ConnectionManager::sendToServer(uint32_t packetId, void* data)
{
    ServerConnection::sendDataToServer(packetId, data);
}

