#include "generalfunctions.h"
#include "CannySearch.h"

using namespace std;
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

void cannyFilter(Mat& src) {
	Mat dst, grayscale, detected_edges;
	Mat thresh;
	dst.create(src.size(), src.type());

	cvtColor(src, grayscale, COLOR_BGR2GRAY);
	createTrackbarsCanny(Canny_Min);

	blur(grayscale, detected_edges, Size(3, 3));
	Canny(detected_edges, detected_edges, Canny_Min, Canny_Min * 3, 3);
	dst = Scalar::all(0);

	src.copyTo(dst, detected_edges);
	cvtColor(dst, dst, COLOR_BGR2GRAY);
	maskThreshold(dst);

	inRange(dst, 80, 100, thresh);


	drawCenterLine(thresh, src, 2);

	imshow("view", src);
}