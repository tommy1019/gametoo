#ifndef ConnectedPlayer_hpp
#define ConnectedPlayer_hpp

#include <SDL_net.h>

class ConnectedPlayer
{
private:
    TCPsocket socket;

public:
    static int startThread(void* obj);

    ConnectedPlayer(TCPsocket socket);
    void run();
};

#endif
