import os
import socket
from PIL import Image, ImageEnhance

# Global Variables
imagebase = "img1.bmp"
imageoverlay = "img2.bmp"
brightness = 50
contrast = 50
isOverlayOn = False  # Track overlay state

def show_image(image_path):
    # Display the specified image using ImageMagick
    os.system("pkill display")  # Close any existing display windows
    os.system("display {} &".format(image_path))  # Display the updated image

def apply_adjustments():
    # Apply brightness, contrast, and overlay, then update the display.
    try:
        # Adjust brightness and contrast on the base image
        with Image.open(imagebase) as base:
            # Ensure consistent mode
            base = base.convert("RGBA")

            # Adjust brightness and contrast
            brightness_factor = brightness / 50.0
            contrast_factor = contrast / 50.0
            brightness_enhancer = ImageEnhance.Brightness(base)
            contrast_enhancer = ImageEnhance.Contrast(base)
            base = brightness_enhancer.enhance(brightness_factor)
            base = contrast_enhancer.enhance(contrast_factor)

            # Save the processed base image as a temporary PNG
            base.save("temp_base.png", "PNG")

    except Exception as e:
        print("Error processing base image:", e)
        return

    # Apply overlay if enabled
    if isOverlayOn:
        # Prepare overlay with transparency using ImageMagick's convert command
        # Assuming white areas should be transparent
        os.system("convert {} -fuzz 10% -transparent white temp_overlay.png".format(imageoverlay))

        # Composite the transparent overlay onto the adjusted base image
        os.system("composite -gravity center temp_overlay.png temp_base.png final_display.png")
    else:
        # Just copy the base image if overlay is off
        os.system("cp temp_base.png final_display.png")

    # Display the final image
    show_image("final_display.png")

# Setup UDP Server
hostname = socket.gethostname()
IPAddr = socket.gethostbyname(hostname)
UDP_IP = "0.0.0.0"
UDP_PORT = 80

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

print("READY")

while True:
    data, addr = sock.recvfrom(1024)
    data_size = len(data)

    if data_size > 85:
        # Transfer original or overlay image
        if ord(data[2]) == 0:  # Transfer original image
            with open(imagebase, "wb") as f:
                f.write(data[4:])
                while True:
                    data, addr = sock.recvfrom(1024)
                    if not data:
                        break
                    f.write(data[4:])
            isOverlayOn = False  # Reset overlay state on original image transfer
            apply_adjustments()  # Display the original image on LCD after transfer

        elif ord(data[2]) == 1:  # Transfer overlay image
            with open(imageoverlay, "wb") as f:
                f.write(data[4:])
                while True:
                    data, addr = sock.recvfrom(1024)
                    if not data:
                        break
                    f.write(data[4:])
            # Display image with overlay if overlay toggle is on
            apply_adjustments()

    elif data_size > 24:
        # Adjust brightness and contrast based on received values
        bnum10 = data[0]
        bnum1 = data[1]
        cnum10 = data[2]
        cnum1 = data[3]
        brightness = int(bnum10) + int(bnum1)
        contrast = int(cnum10) + int(cnum1)
        
        # Apply adjustments and update display
        apply_adjustments()

    elif data_size < 24:
        # Toggle overlay on or off
        overlay = ord(data[0])
        if overlay == 2:
            isOverlayOn = True
        elif overlay == 0:
            isOverlayOn = False
        apply_adjustments()  # Update display based on overlay toggle state
