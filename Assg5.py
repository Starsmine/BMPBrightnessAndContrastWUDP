
import os
import socket
from PIL import Image, ImageEnhance
import cv2


# Global Variables
imagebase = "img1.bmp"
imageoverlay = "img2.bmp"
brightness = 50  # Default brightness (range: 0-100)
contrast = 50    # Default contrast (range: 0-100)
overlay = 0

# Setup UDP Server
UDP_IP = "0.0.0.0"
UDP_PORT = 80

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))
pipe_name = "/tmp/imagepipe"
if not os.path.exists(pipe_name):
        os.mkfifo(pipe_name)

print("READY")

while True:
    data, addr = sock.recvfrom(1024)
    data_size = len(data)

    if data_size > 5:
        # Transfer original or overlay image
        if ord(data[2]) == 0:  # Transfer original image
            with open(imagebase, "wb") as f:
                f.write(data[4:])
                while True:
                    data, addr = sock.recvfrom(1024)
                    if not data:
                        break
                    f.write(data[4:])


        elif ord(data[2]) == 1:  # Transfer overlay image
            with open(imageoverlay, "wb") as f:
                f.write(data[4:])
                while True:
                    data, addr = sock.recvfrom(1024)
                    if not data:
                        break
                    f.write(data[4:])


    elif data_size > 1:
        # Adjust brightness and contrast based on received values
        bnum10 = data[0]
        bnum1 = data[1]
        cnum10 = data[2]
        cnum1 = data[3]
        bnum = bnum10 + bnum1
        cnum = cnum10 + cnum1
        brightness = int(bnum)
        contrast = int(cnum)



    elif data_size == 1:
        # Toggle overlay on or off
        overlay = ord(data[0])

    strb = str(brightness)
    if len(strb) == 1:
        strb = "0" + strb
    #print(strb)

    strc = str(contrast)
    if len(strc) == 1:
        strc = "0" + strc
    data = strb + strc + str(overlay)

    print(data)
    pipe = open(pipe_name, 'w')
    pipe.write(data)
    pipe.close()

    #mylib.process_buffer(data, len(data))


