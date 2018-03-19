#include "ConnectedPlayer.hpp"

int ConnectedPlayer::startThread(void* obj)
{
    ((ConnectedPlayer*)obj)->run();
    return 0;
}

ConnectedPlayer::ConnectedPlayer(TCPsocket socket)
{
    this->socket = socket;
}

void ConnectedPlayer::run()
{
    
}
