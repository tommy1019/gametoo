#ifndef ConnectedPlayer_hpp
#define ConnectedPlayer_hpp

#include <SDL_net.h>

class ConnectedPlayer
{
private:
    static int newPlayerId;

    int playerId;

    TCPsocket socket;
    SDL_sem* socketWriteLock;
public:


    static int startThread(void* obj);

    ConnectedPlayer(TCPsocket socket);
    ~ConnectedPlayer();

    void run();
    void sendData(uint32_t packetId, void *data);
};

#endif
