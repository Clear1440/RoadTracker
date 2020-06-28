#include "BWSearch.h"
#include "generalfunctions.h"

using namespace cv;
using namespace std;

int BW_MIN = 0;
int BW_MAX = 256;

void on_trackbarBW(int, void*) {
	//This function gets called whenever a
	// trackbar position is changed
}

void createTrackbarsBW(int& BW_MIN, int& BW_MAX) {
	namedWindow("Trackbars", 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf_s(TrackbarName, "BW_MIN", BW_MIN);
	sprintf_s(TrackbarName, "BW_MAX", BW_MAX);

	createTrackbar("BW_MIN", "Trackbars", &BW_MIN, 255, on_trackbarBW);
	createTrackbar("BW_MAX", "Trackbars", &BW_MAX, 255, on_trackbarBW);
}


void grayscaleFilter(Mat& Src) {
	Mat gray, threshold;
	cvtColor(Src, gray, COLOR_BGR2GRAY);
	createTrackbarsBW(BW_MIN, BW_MAX);

	inRange(gray, BW_MIN, BW_MAX, threshold);
	maskThreshold(threshold);

	//imshow("grayscale", gray);
	drawCenterLine(threshold, Src);
	imshow("source", Src);
	imshow("thresh", threshold);
	waitKey(1);
}