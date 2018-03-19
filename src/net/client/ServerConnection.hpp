#ifndef ServerConnection_hpp
#define ServerConnection_hpp

#include <SDL_net.h>

class ServerConnection
{
private:

public:
    static int connectToServer(void* data);
};

#endif
