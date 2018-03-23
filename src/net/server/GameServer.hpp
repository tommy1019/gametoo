#ifndef GameServer_hpp
#define GameServer_hpp

#include <vector>
#include <unordered_set>

#include <SDL_net.h>

#include "ConnectedPlayer.hpp"

class GameServer
{
private:
    static std::vector<ConnectedPlayer*> connectedPlayers;
    static std::vector<SDL_Thread*> connectedPlayerThreads;

    static SDL_Thread* syncThread;
public:
    static bool running;
    static int numConnected;

    static int startAcceptionConnections(void* data);

    static void broadcastData(uint32_t packetId, void* data);
};

#endif
