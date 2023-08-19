#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

namespace PROTOCOL
{
    typedef struct
    {
        uint32_t message_id;
        uint16_t mode_cmd;
        uint16_t spare;
        uint32_t rgba;
    } PAYLOAD;
}

#endif