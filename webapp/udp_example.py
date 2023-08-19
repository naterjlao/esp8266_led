import socket
import struct

ip = "239.1.1.1"
port = 4000
# ref https://stackoverflow.com/questions/8437726/can-python-select-what-network-adapter-when-opening-a-socket
INTERFACE = "192.168.4.35"

msg = struct.pack('!L', 0x47454443) # message id
msg+= struct.pack('!B', 0x01) # mode
msg+= struct.pack('!B', 0x00) # spare
msg+= struct.pack('!H', 0x00) # rate
msg+= struct.pack('!B', 0xFF) # red
msg+= struct.pack('!B', 0xFF) # green
msg+= struct.pack('!B', 0xFF) # blue
msg+= struct.pack('!B', 0xFF) # brightness
print(msg)


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((INTERFACE, 0))
sock.sendto(msg, (ip, port))