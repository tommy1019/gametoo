#ifndef GameServer_hpp
#define GameServer_hpp

#include <vector>

#include <SDL_net.h>

#include "ConnectedPlayer.hpp"

class GameServer
{
private:
    static std::vector<ConnectedPlayer*> connectedPlayers;
    static std::vector<SDL_Thread*> connectedPlayerThreads;

public:
    static bool running;

    static int startAcceptionConnections(void* data);
};

#endif
