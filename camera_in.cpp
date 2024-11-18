
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

void readpipe(double& brightness, int& contrast){
        string line;
        while (1) {
                ifstream pipe("/tmp/imagepipe");
                getline(pipe, line);
                brightness = stoi(line.substr(0,2));
                contrast = stoi(line.substr(2,2));
                cout << "b: "<< brightness << endl;
                cout << "c: "<< contrast << endl;
        }
}

int main()
{
    Mat src;
    Mat overlay;
    Mat overlayR;
    Mat outimage;

    overlay = imread("img2.bmp", IMREAD_GRAYSCALE);

    D8MCapture *cap = new D8MCapture(TV_DECODER_TERASIC_STREAM_CAPTURE_BASE, CAPTURE_RAM_DEVICE);
    if (!cap->isOpened()) {
        return -1;
    }

    char str[100];
    static struct timeval last_time;
    struct timeval current_time;
    static float last_fps;
    float t;
    float fps;
    double brightness = 1.0;
    int contrast = 0;

    namedWindow("camera");

    auto first = thread(readpipe, ref(brightness), ref(contrast));

    resize(overlay, overlayR, Size(800, 480));
    //overlayR = overlayR.reshape(4,0);
    //resize(overlayR, overlayR, Size(800, 480));

    /*for (int y = 0; y < overlayR.rows; y++){
        for (int x = 0; x < overlayR.cols; x++){
         Vec4b & pixel = overlayR.at<Vec4b>(y, x);
         if (!(pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255)){
                pixel[0] = 0; pixel[1] = 0; pixel[2] = 0;
        }
     }
    }*/

    imwrite("img3.png", overlayR);


    while (1) {
        if (!cap->read(src))
            return -1;


        //imwrite("source.jpg", src);

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

        if(src.empty() ){cout << "Error loading src" << endl; return EXIT_FAILURE; }
        if(overlayR.empty() ){cout << "Error loading overlay" << endl; return EXIT_FAILURE; }
        //cout << "overlaydepth : " << overlayR.channels() << endl;
        //cout << "sourceepth : " << src.channels() << endl;
        //addWeighted(src, 0.1, overlayR, 0.9, 0.0, outimage, -1);
        bitwise_and(src, src, outimage, overlayR);
        //imwrite("out.jpg", outimage);
        imshow("camera", outimage);

        //-- bail out if escape was pressed
        int c = waitKey(10);
        if ((char) c == 27) {
            break;
        }


    }
    delete cap;
    destroyAllWindows();

    return 0;
}
