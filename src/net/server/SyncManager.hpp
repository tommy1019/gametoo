#ifndef SyncManager_hpp
#define SyncManager_hpp

#include <utility>
#include <vector>
#include <unordered_set>

#include <SDL.h>

class SyncManager
{
public:
    static SDL_sem* dataLock;

    static int run(void* data);
};

#endif
