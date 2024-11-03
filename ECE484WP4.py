import mmap
import os
import time
import socket
from PIL import Image
import struct

hostname = socket.gethostname()
IPAddr = socket.gethostbyname(hostname)
# UDP Server Info
UDP_IP = "0.0.0.0"
UDP_PORT = 80

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))
filename = "img1.bmp"
# UDP Server Listener
print("READY")
with open(filename, "wb") as f:
        while True:
                #recieve 4 byte
                data, addr = sock.recvfrom(1026)
                if not data:
                        break
                f.write(data[2:])
                number = ord(data[1])

                print(number)



