#include <opencv2/opencv.hpp>
#include <sys/time.h>
#include "D8MCapture.h"
#include "hps_0.h"
#include <iostream>
#include <string>
#include <fstream>
#include <thread>

using namespace cv;
using namespace std;

#ifndef CAPTURE_RAM_DEVICE
#define CAPTURE_RAM_DEVICE "/dev/f2h-dma-memory"
#endif /* ifndef CAPTURE_RAM_DEVICE */

// Function to read brightness, contrast, and overlay state from the pipe
void readPipe(double &brightness, double &contrast, bool &overlayOn) {
    string line;
    while (true) {
        ifstream pipe("/tmp/imagepipe");
        if (pipe.is_open()) {
            getline(pipe, line);
            if (line.size() >= 5) {
                brightness = stoi(line.substr(0, 2));
                contrast = stoi(line.substr(2, 2));
                overlayOn = stoi(line.substr(4, 1)) == 1;
            }
            pipe.close();
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

// Adjust brightness based on factor
void adjustBrightness(Mat &frame, double factor) {
    if (factor != 1.0) {
        frame.convertTo(frame, -1, factor, 0);
    }
}

// Adjust contrast based on factor
void adjustContrast(Mat &frame, double factor) {
    Mat meanMat;
    Scalar meanIntensity = mean(frame);
    frame.convertTo(frame, CV_32F); // Convert to float for accurate scaling

    // Scale intensity values relative to the mean intensity
    frame = (frame - meanIntensity[0]) * factor + meanIntensity[0];
    frame.convertTo(frame, CV_8U); // Convert back to 8-bit
}

int main() {
    Mat src, overlay, overlayResized, mask, finalFrame;
    double brightness = 50.0;  // Default brightness (range: 0-99)
    double contrast = 50.0;    // Default contrast (range: 0-99)
    bool overlayOn = false;    // Toggle overlay state

    // Load the overlay image
    overlay = imread("img2.bmp", IMREAD_GRAYSCALE);
    if (overlay.empty()) {
        cerr << "Error: Unable to load img2.bmp!" << endl;
        return -1;
    }

    // Resize the overlay to match the camera resolution
    Size targetSize(800, 480); // Update if the resolution changes
    resize(overlay, overlayResized, targetSize);

    // Create a binary mask for overlay application
    threshold(overlayResized, mask, 200, 255, THRESH_BINARY); // Mask for white regions

    // Initialize the camera
    D8MCapture *cap = new D8MCapture(TV_DECODER_TERASIC_STREAM_CAPTURE_BASE, CAPTURE_RAM_DEVICE);
    if (!cap->isOpened()) {
        cerr << "Error: Unable to open video capture device!" << endl;
        return -1;
    }

    // Start a thread to read brightness and contrast values from the pipe
    thread pipeThread(readPipe, ref(brightness), ref(contrast), ref(overlayOn));

    namedWindow("LCD Output");

    while (true) {
        // Capture a frame from the camera
        if (!cap->read(src)) {
            cerr << "Error: Unable to read frame from camera!" << endl;
            break;
        }

        // Resize the camera frame to match overlay resolution
        resize(src, src, targetSize);

        //fps counter for displaying performance
        gettimeofday(&current_time, NULL);
        t = (current_time.tv_sec - last_time.tv_sec)
            + (current_time.tv_usec - last_time.tv_usec) / 1000000.;
        fps = 1. / t;
        fps = last_fps * 0.8 + fps * 0.2;
        last_fps = fps;
        last_time = current_time;
        sprintf(str, "%2.2f, %2.6f", fps, t);
        putText(src, str, Point(20, 40), FONT_HERSHEY_DUPLEX, 1,
            Scalar(0, 255, 0));

        // Adjust brightness
        double brightnessFactor = brightness / 50.0;
        brightnessFactor = pow(brightnessFactor, 3.0); // Apply non-linear scaling
        adjustBrightness(src, brightnessFactor);

        // Adjust contrast
        double contrastFactor = contrast / 50.0;
        if (contrastFactor > 1.0) {
            contrastFactor = pow(contrastFactor, 3.0); // Increase effect for contrast > 50
        }
        adjustContrast(src, contrastFactor);

        // Apply overlay if enabled
        if (overlayOn) {
            bitwise_and(src, src, finalFrame, mask); // Use mask to apply overlay
        } else {
            finalFrame = src.clone();
        }  

        // Display the final output on the LCD screen
        imshow("LCD Output", finalFrame);

        // Exit if 'ESC' key is pressed
        if (waitKey(10) == 27) {
            break;
        }
    }

    // Cleanup
    pipeThread.detach();
    delete cap;
    destroyAllWindows();

    return 0;
}
