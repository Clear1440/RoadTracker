#include "generalfunctions.h"

using namespace cv;
using namespace std;

void morphOps(Mat& thresh) {
	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

	//erode(thresh, thresh, erodeElement);

	//dilate(thresh, thresh, dilateElement);
	//dilate(thresh, thresh, dilateElement);

	erode(thresh, thresh, erodeElement);
}

void maskThreshold(Mat& thresh) {
	//for first half
	for (int i = 0; i < thresh.cols; i++) {
		for (int j = 0; j < thresh.rows; j++) {
			if (j - i > 0) {//bounding slants
				thresh.at<unsigned char>(j - i - 1, i) = 0;
				thresh.at<unsigned char>(j - i - 1, thresh.cols - i - 1) = 0;//mirror
			}

			if (j < thresh.rows / 2) {//take out top half
				thresh.at<unsigned char>(j, i) = 0;
			}
		}
	}
}


void drawCenterLine(const Mat thresh, Mat& drawOn) {
	int midpoint = (drawOn.cols / 2);
	int LborderPos = 0, RborderPos = 0, counter = 0;

	for (int i = thresh.rows - 50; i > thresh.rows / 2; i--) {
		for (int j = 0; j < thresh.cols; j++) {
			if (thresh.at<unsigned char>(i, j) > 0) {
				counter++;
			}
			else {
				counter = 0;
			}

			if ((counter > 4) && (j < thresh.cols / 2)) {//we want last available left boarder
				LborderPos = j;
				counter = 0;
			}
			else if ((counter > 4) && (RborderPos == 0) && (j > thresh.cols / 2)) {//we want first available right boarder
				RborderPos = j;
				counter = 0;
				break;
			}
		}

		if ((RborderPos > 0) && (LborderPos > 0)) {//actually found something
			line(drawOn, { LborderPos, i }, { LborderPos, i }, Scalar(255, 0, 0), 2);//draw red  border
			line(drawOn, { RborderPos, i }, { RborderPos, i }, Scalar(0, 0, 255), 2);//draw blue border

			midpoint = (LborderPos + RborderPos) / 2;
			line(drawOn, { midpoint, i }, { midpoint, i }, Scalar(0, 255, 0), 2);
		}
		//clean-up for next round
		counter = 0;
		RborderPos = 0;
		LborderPos = 0;
	}
}