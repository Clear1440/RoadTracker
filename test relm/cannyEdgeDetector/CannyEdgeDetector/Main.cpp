#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

int Canny_Min = 0;

void on_trackbarCanny(int, void*) {
    //This function gets called whenever a
    // trackbar position is changed
}

void createTrackbarsCanny(int& Canny_MIN) {
    namedWindow("Trackbars", 0);
    //create memory to store trackbar name on window
    char TrackbarName[50];
    sprintf_s(TrackbarName, "Canny_MIN", Canny_MIN);
    createTrackbar("Canny_MIN", "Trackbars", &Canny_MIN, 100, on_trackbarCanny);
}

void TakeCanny(Mat src) {
    Mat dst, grayscale, detected_edges;
    dst.create(src.size(), src.type());

    cvtColor(src, grayscale, COLOR_BGR2GRAY);
    createTrackbarsCanny(Canny_Min);

    blur(grayscale, detected_edges, Size(3, 3));
    Canny(detected_edges, detected_edges, Canny_Min, Canny_Min * 3, 3);
    dst = Scalar::all(0);

    src.copyTo(dst, detected_edges);
    imshow("dst", dst);
}


int main(int argc, char** argv)
{
    CommandLineParser parser(argc, argv, "{@input | fruits.jpg | input image}");
    Mat src = imread("sample2.PNG", IMREAD_COLOR); // Load an image
       
    while (1) {
        TakeCanny(src);
        waitKey(30);
    }

    return 0;
}