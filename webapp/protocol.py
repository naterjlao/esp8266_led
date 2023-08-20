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

def parse_mode(input: str):
    if input == "solid":
        mode = Mode.SOLID
    elif input == "breathe":
        mode = Mode.BREATHE
    elif input == "cycle":
        mode = Mode.CYCLE
    elif input == "breathe_cycle":
        mode = Mode.BREATHE_CYCLE
    elif input == "chaser":
        mode = Mode.CHASER
    else:
        mode = Mode.OFF
    return mode

def parse_rate(input: str):
    return int(input)

def parse_color(input: str):
    return int(input[1:], 16)

def parse_brightness(input: str):
    return int(input)

def pack_payload(mode_cmd: Mode = Mode.OFF, rate: int = 0x0, color: int = 0xFFFFFF, brightness: int = 0xFF):
    '''!
        @brief Generates the LED UDP Protocol packet
    '''
    MESSAGE_ID = 0x4C454443

    red = (color >> 16) & 0xFF
    green = (color >> 8) & 0xFF
    blue = (color >> 0) & 0xFF

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
    msg+= struct.pack('!B', brightness)
    
    return msg

if __name__ == "__main__":
    print(pack_payload(Mode.BREATHE_CYCLE, 128, 0xAABBCC, 0xDD))