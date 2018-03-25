#ifndef ServerConnection_hpp
#define ServerConnection_hpp

#include <SDL_net.h>

#include "../../GameState.hpp"

class ServerConnection
{
private:
    static TCPsocket socket;
    static SDL_sem* socketWriteLock;

    static GameState* gameState;
public:
    static bool running;

    static int connectToServer(void* data);
    static void sendDataToServer(uint32_t packetId, uint64_t dataSize, void* data);
};

#endif
