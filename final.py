import os
import socket

# Global Variables
camera_in_folder = "/path/to/camera_in"  # Absolute path to the camera_in folder
imageoverlay = os.path.join(camera_in_folder, "img2.bmp")
brightness = 50  # Default brightness (range: 0-99)
contrast = 50    # Default contrast (range: 0-99)
overlay_state = 0  # 0: Off, 1: On
pipe_name = "/tmp/imagepipe"

# Setup UDP Server
UDP_IP = "0.0.0.0"
UDP_PORT = 80

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

# Ensure the camera_in folder exists
if not os.path.exists(camera_in_folder):
    os.makedirs(camera_in_folder)

if not os.path.exists(pipe_name):
    os.mkfifo(pipe_name)

print("Python receiver ready...")

while True:
    data, addr = sock.recvfrom(1024)
    if len(data) > 4:
        # Overlay image transfer
        if ord(data[2]) == 1:  # Overlay image transfer command
            with open(imageoverlay, "wb") as f:
                f.write(data[4:])
                while True:
                    data, addr = sock.recvfrom(1024)
                    if not data:
                        break
                    f.write(data[4:])
            overlay_state = 1  # Turn overlay on
            print("Overlay image received and stored in camera_in folder.")

    elif len(data) > 1:
        # Brightness and contrast adjustments
        brightness = int(data[:2])
        contrast = int(data[2:4])
        print("Brightness: {}, Contrast: {}".format(brightness, contrast))

    elif len(data) == 1:
        # Toggle overlay state
        overlay_state = ord(data[0])
        print("Overlay state: {}".format("On" if overlay_state else "Off"))

    # Write updated values to the pipe
    with open(pipe_name, 'w') as pipe:
        pipe.write("{:02}{:02}{}".format(brightness, contrast, overlay_state))
