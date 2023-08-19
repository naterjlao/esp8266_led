#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

namespace PROTOCOL
{
    /// @brief Defines the operational modes for the LED strip.
    /// @todo move to protocol.h
    enum MODES: uint16_t
    {
        OFF = 0x0,
        SOLID = 0x1,
        BREATHE = 0x2,
        CYCLE = 0x3,
        BREATHE_CYCLE = 0x4,
        CHASER = 0x5
    };

    typedef struct
    {
        uint32_t message_id;
        MODES mode_cmd;
        uint16_t spare;
        uint32_t rgba;
    } PAYLOAD;
}

#endif