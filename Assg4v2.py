import os
import socket
from PIL import Image, ImageEnhance

# Global Variables
imagebase = "img1.bmp"
imageoverlay = "img2.bmp"
brightness = 50  # Default brightness (range: 0-100)
contrast = 50    # Default contrast (range: 0-100)
isOverlayOn = False  # Track overlay state

def show_image(image_path):
    # Display the specified image using ImageMagick
    os.system("pkill display")  # Close any existing display windows
    os.system("display {} &".format(image_path))  # Display the updated image

def apply_adjustments():
    # Apply brightness, contrast, and overlay, then update the display.
    try:
        # Open the base image and ensure it is in a consistent mode
        with Image.open(imagebase) as base:
            base = base.convert("RGBA")

            # Adjust brightness
            brightness_factor = brightness / 50.0  # Center at 1.0
            brightness_enhancer = ImageEnhance.Brightness(base)
            base = brightness_enhancer.enhance(brightness_factor)

            # Adjust contrast with modified scaling
            contrast_factor = contrast / 50.0
            if contrast_factor > 1:
                contrast_factor = contrast_factor ** 2  # Increase contrast effect for values > 50
            contrast_enhancer = ImageEnhance.Contrast(base)
            base = contrast_enhancer.enhance(contrast_factor)

            # Save the processed base image as a temporary PNG
            base.save("temp_base.png", "PNG")
            print(f"Brightness: {brightness}, Contrast: {contrast}")

    except Exception as e:
        print("Error processing base image:", e)
        return

    # Apply overlay if enabled
    if isOverlayOn:
        # Prepare overlay with transparency using ImageMagick's convert command
        os.system("convert {} -fuzz 10% -transparent white temp_overlay.png".format(imageoverlay))
        # Composite the transparent overlay onto the adjusted base image
        os.system("composite -gravity center temp_overlay.png temp_base.png final_display.png")
    else:
        # Just copy the base image if overlay is off
        os.system("cp temp_base.png final_display.png")

    # Display the final image
    show_image("final_display.png")

# Setup UDP Server
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
        
        # Apply adjustments and update display
        apply_adjustments()

    elif data_size == 1:
        # Toggle overlay on or off
        overlay = ord(data[0])
        isOverlayOn = overlay == 2
        apply_adjustments()  # Update display based on overlay toggle state
