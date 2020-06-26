#include "HSVsearch.h"

void drawCenterLine(const Mat thresh, Mat& drawOn) {
	int midpoint = (drawOn.cols / 2);
	int LborderPos = 0, RborderPos = 0, counter = 0;
	bool foundInner = false;
	bool prevCol = false, currCol = false;

	for (int i = thresh.rows - 50; i > thresh.rows / 2; i--) {
		for (int j = 0; j < thresh.cols; j++) {
			prevCol = currCol;

			if (thresh.at<unsigned char>(i, j) > 0) {
				counter++;
			}
			else {
				counter = 0;
			}

			if ((counter > 4) && (foundInner == false) && (j < thresh.cols / 2)) {
				foundInner = true;
				LborderPos = j;
				counter = 0;
			}
			else if ((counter > 4) && (foundInner == true) && (j > thresh.cols / 2)) {
				RborderPos = j;
				counter = 0;
			}
		}

		if ((RborderPos > 0) && (LborderPos > 0)) {//actually found something
			line(drawOn, { LborderPos, i }, { LborderPos, i }, Scalar(255, 0, 0), 2);//draw red  border
			line(drawOn, { RborderPos, i }, { RborderPos, i }, Scalar(0, 0, 255), 2);//draw blue border

			midpoint = (LborderPos + RborderPos) / 2;
			line(drawOn, { midpoint, i }, { midpoint, i }, Scalar(0, 255, 0), 2);
		}
		//clean-up for next round
		foundInner = false;
		counter = 0;
		RborderPos = 0;
		LborderPos = 0;
	}
}

void maskThreshold(Mat& thresh) {
	//for first half
	for (int i = 0; i < thresh.cols; i++) {
		for (int j = 0; j < thresh.rows; j++) {

			if (j - i > 0) {//bounding slants
				thresh.at<unsigned char>(j - i - 1, i) = 0;
				thresh.at<unsigned char>(j - i - 1, thresh.cols - i - 1) = 0;//mirror
			}

			if (j < thresh.rows / 2) {//take out top 3rd
				thresh.at<unsigned char>(j, i) = 0;
			}

		}
	}

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
	createTrackbar("H_MIN", "Trackbars", &H_MIN, H_MAX, on_trackbar);
	createTrackbar("H_MAX", "Trackbars", &H_MAX, H_MAX, on_trackbar);
	createTrackbar("S_MIN", "Trackbars", &S_MIN, S_MAX, on_trackbar);
	createTrackbar("S_MAX", "Trackbars", &S_MAX, S_MAX, on_trackbar);
	createTrackbar("V_MIN", "Trackbars", &V_MIN, V_MAX, on_trackbar);
	createTrackbar("V_MAX", "Trackbars", &V_MAX, V_MAX, on_trackbar);
}

void morphOps(Mat& thresh) {
	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

	//erode(thresh, thresh, erodeElement);

	//dilate(thresh, thresh, dilateElement);
	//dilate(thresh, thresh, dilateElement);

	erode(thresh, thresh, erodeElement);

}

void on_trackbar(int, void*) {
	//This function gets called whenever a
	// trackbar position is changed
}