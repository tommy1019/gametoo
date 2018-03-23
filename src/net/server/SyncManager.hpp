#ifndef SyncManager_hpp
#define SyncManager_hpp

#include <unordered_set>

#include <SDL.h>

class SyncManager
{
private:
    static SDL_sem* setLock;
    static std::unordered_set<int> respondedPlayers;

    static std::atomic_int inputsReceived;
public:
    static int run(void* data);

    static void handelClientInput(int playerId);
};

#endif
