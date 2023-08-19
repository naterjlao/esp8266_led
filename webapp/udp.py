import socket
import protocol

ip = "239.1.1.1"
port = 4000
# ref https://stackoverflow.com/questions/8437726/can-python-select-what-network-adapter-when-opening-a-socket
INTERFACE = "192.168.4.35"

class UDPMulticastIO:
    def __init__(self, ip: str, port: int, interface: str):
        self.ip = ip
        self.port = port

        # Setup socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind((interface, 0))

    def send(self, payload: bytes):
        return self.sock.sendto(payload, (self.ip, self.port))
    
if __name__ == "__main__":
    IP = "239.1.1.1"
    PORT = 4000
    INTERFACE = "192.168.4.54"
    # NOTE: interface dependent on host machine
    # ref https://stackoverflow.com/questions/8437726/can-python-select-what-network-adapter-when-opening-a-socket
    
    udp_io = UDPMulticastIO(IP, PORT, INTERFACE)
    msg = protocol.pack_payload(protocol.Mode.BREATHE_CYCLE, 128, 0xAA, 0xBB, 0xCC, 0xDD)
    udp_io.send(msg)
    