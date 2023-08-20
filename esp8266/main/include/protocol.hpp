#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

namespace PROTOCOL
{
    const uint32_t MESSAGE_ID = 0x4C454443;

    /// @brief Defines the operational modes for the LED strip.
    /// @note The values here must match the UDP payload
    enum MODES: uint8_t
    {
        OFF = 0x0,
        SOLID = 0x1,
        BREATHE = 0x2,
        CYCLE = 0x3,
        BREATHE_CYCLE = 0x4,
        CHASER = 0x5
    };

    /// @brief Defines the UDP payload contents
    typedef struct
    {
        uint32_t message_id;
        MODES mode_cmd;
        uint8_t spare;
        uint16_t rate;
        uint32_t rgba;
    } PAYLOAD;
}

#endif