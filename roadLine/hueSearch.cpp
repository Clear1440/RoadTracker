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

void createTrackbarsHSV(int& H_MINp, int& H_MAXp, int& S_MINp, int& S_MAXp, int& V_MINp, int& V_MAXp) {
	//create window for trackbars
	namedWindow("Trackbars", 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf_s(TrackbarName, "H_MIN", H_MINp);
	sprintf_s(TrackbarName, "H_MAX", H_MAXp);
	sprintf_s(TrackbarName, "S_MIN", S_MINp);
	sprintf_s(TrackbarName, "S_MAX", S_MAXp);
	sprintf_s(TrackbarName, "V_MIN", V_MINp);
	sprintf_s(TrackbarName, "V_MAX", V_MAXp);
	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
	//the max value the trackbar can move (eg. H_HIGH), 
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->      
	createTrackbar("H_MIN", "Trackbars", &H_MINp, 255, on_trackbarHSV);
	createTrackbar("H_MAX", "Trackbars", &H_MAXp, 255, on_trackbarHSV);
	createTrackbar("S_MIN", "Trackbars", &S_MINp, 255, on_trackbarHSV);
	createTrackbar("S_MAX", "Trackbars", &S_MAXp, 255, on_trackbarHSV);
	createTrackbar("V_MIN", "Trackbars", &V_MINp, 255, on_trackbarHSV);
	createTrackbar("V_MAX", "Trackbars", &V_MAXp, 255, on_trackbarHSV);
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