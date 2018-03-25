#include <stdint.h>

struct Packet
{
    uint32_t packetId;
    uint64_t dataSize;
    uint8_t* data;
};
