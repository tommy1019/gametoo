#include "ConnectionManager.hpp"

#include <iostream>

#include "server/GameServer.hpp"
#include "client/ServerConnection.hpp"

SDL_Thread* ConnectionManager::gameServerThread;
SDL_Thread* ConnectionManager::connectionThread;

SDL_sem* ConnectionManager::dataLock;

std::vector<Packet*> ConnectionManager::unprocessedPackets;

void ConnectionManager::startMPServer()
{
    gameServerThread = SDL_CreateThread(GameServer::startAcceptionConnections, "GameServer", nullptr);
}

void ConnectionManager::connectToServer()
{
    dataLock = SDL_CreateSemaphore(1);

    connectionThread = SDL_CreateThread(ServerConnection::connectToServer, "ServerConnection", nullptr);
}

void ConnectionManager::sendToServer(uint32_t packetId, uint64_t dataSize, void* data)
{
    ServerConnection::sendDataToServer(packetId, dataSize, data);
}

