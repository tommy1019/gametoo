#ifndef ConnectionManager_hpp
#define ConnectionManager_hpp

#include <SDL_thread.h>

#include "../GameState.hpp"

class ConnectionManager
{
private:
    static SDL_Thread* gameServerThread;
    static SDL_Thread* connectionThread;

public:
    static void startMPServer();
    static void connectToServer(GameState* clientGameState);
};

#endif
