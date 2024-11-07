import mmap
import os
import time
import socket
from PIL import Image, ImageDraw, ImageEnhance
import struct

def showimg():
        with Image.open (imagebase) as im:
                im.show()
def modbrightness():
        with Image.open (imagebase) as im:
            factor = brightness/50.0
            enhancer = ImageEnhance.Brightness(im)
            enhanced_image = enhancer.enhance(factor)
            enhanced_image.save(imagebase) #save the image to retain change.
            enhanced_image.show() #Displaying the adjusted image
                
def modcontrast():
    with Image.open (imagebase) as im:
        factor = contrast/50.0 #Calculating the factor based on the received contrast value
        enhancer = ImageEnhance.Contrast(im) #Initializing the contrast enhancer
        enhanced_image = enhancer.enhance(factor) #Applying the contrast adjustment
        enhanced_image.save(imagebase) #save the image to retain change.
        enhanced_image.show() #Displaying the adjusted image
        
def overlayimg(isOverlay):
        if isOverlay:
            with Image.open(imagebase) as base, Image.open(imageoverlay) as overlay:
                base = base.convert("RGBA")
                overlay = overlay.convert("RGBA")
            
                #overlaying the images
                combinedImage = Image.alpha_composite(base, overlay) #base beneath overlay
                combinedImage.show()
                combinedImage.save("combinedImage.bmp")

hostname = socket.gethostname()
IPAddr = socket.gethostbyname(hostname)
# UDP Server Info
UDP_IP = "0.0.0.0"
UDP_PORT = 80

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))
imagebase = "img1.bmp"
imageoverlay = "img2.bmp"
brightness = 50
contrast = 50
overlay = 0

# UDP Server Listener
print("READY")
while True:
        data, addr = sock.recvfrom(1024)
        print (int(data.__sizeof__()))
        if data.__sizeof__() > 85:
                if ord(data[2]) == 0:
                        with open(imagebase, "wb") as f:
                                if not data:
                                        f.close()
                                        showimg()
                                        break
                                f.write(data[4:])
                                number = ord(data[1])
                                print(number)

                                while True:
                                        data, addr = sock.recvfrom(1024)
                                        if not data:
                                                f.close()
                                                showimg()
                                                break
                                        f.write(data[4:])
                                        number = ord(data[1])
                                        print(number)
                elif ord(data[2]) == 1:
                        with open(imageoverlay, "wb") as f:
                                if not data:
                                        break
                                f.write(data[4:])
                                number = ord(data[1])
                                print(number)

                                while True:
                                        data, addr = sock.recvfrom(1024)
                                        if not data:
                                                f.close()
                                                break
                                        f.write(data[4:])
                                        number = ord(data[1])
                                        print(number)

        elif data.__sizeof__() > 24:
                bnum10 = data[0]
                bnum1 = data[1]
                cnum10 = data[2]
                cnum1 = data[3]
                bnum = bnum10 + bnum1
                cnum = cnum10 + cnum1
                print("brightness = " + bnum)
                print("contrast = " + cnum)
                brightness = int(bnum)
                contrast = int(cnum)
                
                #Applying brightness and contrast
                modbrightness()
                modcontrast()
                
        elif data.__sizeof__() < 24:
                overlay = ord(data[0])
                if overlay == 2:
                        overlayimg(True)
                elif overlay == 0:
                        overlayimg(False)
