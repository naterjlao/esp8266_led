import socket

ip = "239.1.1.1"
port = 4000
msg = b"foobar"
# ref https://stackoverflow.com/questions/8437726/can-python-select-what-network-adapter-when-opening-a-socket
INTERFACE = "192.168.4.35"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((INTERFACE, 0))
sock.sendto(msg, (ip, port))