#include "hsvSearch.h"

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

/* Marks for white in sample.PNG*/
/*
	H_MIN = 35;
	H_MAX = 138;
	S_MIN = 0;
	S_MAX = 25;
	V_MIN = 168;
	V_MAX = 256;
	*/

/* Marks for white in sample.mp4*/
/*
	H_MIN = 4;
	H_MAX = 256;
	S_MIN = 0;
	S_MAX = 245;
	V_MIN = 129;
	V_MAX = 171;
	*/



int main(int argc, char* argv[]) {
	Mat SamplePhoto, HSV, threshold;

	VideoCapture cap("sample3.mp4");

	createTrackbarsHSV(H_MIN, H_MAX, S_MIN, S_MAX, V_MIN, V_MAX);
	
	while (1) {
		//SamplePhoto = imread("sample2.PNG", IMREAD_COLOR);//refresh
		
		cap >> SamplePhoto;

		cvtColor(SamplePhoto, HSV, COLOR_BGR2HSV);

		inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
		//morphOps(threshold);
		maskThreshold(threshold);
		
		//show frames 
		imshow("Thresholded Image", threshold);
		//imshow("Original Image", SamplePhoto);
		//imshow("HSV Image", HSV);
		drawCenterLine(threshold, SamplePhoto);
		imshow("with line", SamplePhoto);
		waitKey(1);

	}
	return 0;
}


