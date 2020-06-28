#include "hsvSearch.h"
#include "generalfunctions.h"

using namespace cv;
using namespace std;

//initial min and max HSV filter values.
//these will be changed using trackbars
int H_MIN = 0;
int H_MAX = 256;
int S_MIN = 0;
int S_MAX = 256;
int V_MIN = 0;
int V_MAX = 256;

void on_trackbarHSV(int, void*) {
	//This function gets called whenever a
	// trackbar position is changed
}

void createTrackbarsHSV(int& H_MIN, int& H_MAX, int& S_MIN, int& S_MAX, int& V_MIN, int& V_MAX) {
	//create window for trackbars
	namedWindow("Trackbars", 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf_s(TrackbarName, "H_MIN", H_MIN);
	sprintf_s(TrackbarName, "H_MAX", H_MAX);
	sprintf_s(TrackbarName, "S_MIN", S_MIN);
	sprintf_s(TrackbarName, "S_MAX", S_MAX);
	sprintf_s(TrackbarName, "V_MIN", V_MIN);
	sprintf_s(TrackbarName, "V_MAX", V_MAX);
	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
	//the max value the trackbar can move (eg. H_HIGH), 
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->      
	createTrackbar("H_MIN", "Trackbars", &H_MIN, 255, on_trackbarHSV);
	createTrackbar("H_MAX", "Trackbars", &H_MAX, 255, on_trackbarHSV);
	createTrackbar("S_MIN", "Trackbars", &S_MIN, 255, on_trackbarHSV);
	createTrackbar("S_MAX", "Trackbars", &S_MAX, 255, on_trackbarHSV);
	createTrackbar("V_MIN", "Trackbars", &V_MIN, 255, on_trackbarHSV);
	createTrackbar("V_MAX", "Trackbars", &V_MAX, 255, on_trackbarHSV);
}

void HSVFilter(Mat& Src) {
	Mat HSV, threshold;
	createTrackbarsHSV(H_MIN, H_MAX, S_MIN, S_MAX, V_MIN, V_MAX);
	cvtColor(Src, HSV, COLOR_BGR2HSV);
	inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);

	//morphOps(threshold);
	maskThreshold(threshold);

	//show frames 
	imshow("Thresholded Image", threshold);
	//imshow("Original Image", SamplePhoto);
	//imshow("HSV Image", HSV);
	drawCenterLine(threshold, Src);
	imshow("with line", Src);
	waitKey(1);
}