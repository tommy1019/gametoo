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

    static SDL_sem* setLock;
    static std::unordered_set<int> respondedPlayers;
public:
    static bool running;

    static int numConnected;
    static int inputsReceived;

    static int startAcceptionConnections(void* data);

    static void broadcastData(uint32_t packetId, void* data);
    static void onInput(int playerId);
};

#endif
