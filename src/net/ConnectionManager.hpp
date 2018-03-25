#ifndef ConnectionManager_hpp
#define ConnectionManager_hpp

#include <vector>

#include <SDL_thread.h>

#include "../GameState.hpp"
#include "Packet.hpp"

class ConnectionManager
{
private:
    static SDL_Thread* gameServerThread;
    static SDL_Thread* connectionThread;

public:
    static SDL_sem* dataLock;
    static std::vector<Packet*> unprocessedPackets;

    static void startMPServer();
    static void connectToServer();

    static void sendToServer(uint32_t packetId, uint64_t dataSize, void* data);
};

#endif
