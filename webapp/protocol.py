import enum
import struct

# Note: must be compliant with protocol.hpp
class Mode(enum.IntEnum):
    OFF = 0x0
    SOLID = 0x1
    BREATHE = 0x2
    CYCLE = 0x3
    BREATHE_CYCLE = 0x4
    CHASER = 0x5

def pack_payload(mode_cmd: Mode = Mode.OFF, rate: int = 0x0,
                 red: int = 0xFF, green: int = 0xFF, blue: int = 0xFF, alpha: int = 0xFF):
    '''!
        @brief Generates the LED UDP Protocol packet
    '''
    MESSAGE_ID = 0x47454443

    # Byte 0-3
    msg = struct.pack('!L', MESSAGE_ID)

    # Byte 4-7
    msg+= struct.pack('!B', mode_cmd)
    msg+= struct.pack('!B', 0x00) # spare
    msg+= struct.pack('!H', rate)

    # Byte 8-12
    msg+= struct.pack('!B', red)
    msg+= struct.pack('!B', green)
    msg+= struct.pack('!B', blue)
    msg+= struct.pack('!B', alpha)
    
    return msg

if __name__ == "__main__":
    print(pack_payload(Mode.BREATHE_CYCLE, 128, 0xAA, 0xBB, 0xCC, 0xDD))