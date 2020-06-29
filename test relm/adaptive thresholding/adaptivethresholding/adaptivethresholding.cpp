#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int Cp = 3;
int BlockNeighborhood = 3;


void createTrackbars();

int main(){
    Mat src, grayscale, thresh;
    src = imread("multishade.png", IMREAD_COLOR);//refresh
    cvtColor(src, grayscale, COLOR_BGR2GRAY);
    createTrackbars();
    int C = 3;
    int B = 3;

    while (1) {
        C = Cp;
        B = BlockNeighborhood;

        
        adaptiveThreshold(grayscale, thresh, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, B, C);

        imshow("thresh", thresh);
        waitKey(30);
    }
}



void on_trackbar(int, void*) {
    //This function gets called whenever a
    // trackbar position is changed
    if (BlockNeighborhood <= 3) {
        BlockNeighborhood = 3;
    }
    else if (BlockNeighborhood >= 50) {
        BlockNeighborhood = 49;
    }

    if (BlockNeighborhood % 2 == 0) {
        BlockNeighborhood++;
    }
}
void createTrackbars() {
    namedWindow("Trackbars", 0);
    //create memory to store trackbar name on window
    char TrackbarName[50];
    sprintf_s(TrackbarName, "C", Cp);
    sprintf_s(TrackbarName, "C", Cp);

    createTrackbar("C", "Trackbars", &Cp, 50, on_trackbar);
    createTrackbar("BlockNeighborhood", "Trackbars", &BlockNeighborhood, 50, on_trackbar);
}
