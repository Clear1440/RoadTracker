#include "opencv2\opencv.hpp"
#include "DftFilter.h"

using namespace cv;
using namespace std;



int main() {
	Mat cameraFeed, cameraFeedGray, returnedFromDFT;
	VideoCapture capture;

	capture.open(0);
	capture.set(CAP_PROP_FRAME_WIDTH, 1920/4);
	capture.set(CAP_PROP_FRAME_HEIGHT, 1080/4);

	while (1) {
		capture.read(cameraFeed);//take in cam feed and place it in cameraFeed Metrix
		cvtColor(cameraFeed, cameraFeedGray, COLOR_RGB2GRAY);
		
		Mat cameraFloat;
		cameraFeedGray.convertTo(cameraFloat, CV_32FC1, 1.0 / 255.0);

		Mat dftOfOrigional;
		takeDFT(cameraFloat, dftOfOrigional);
		showDFT(dftOfOrigional);
		
		Mat filtered;
		lowPassDFTFilter(dftOfOrigional, filtered);
		//imshow("filtered", filtered);

		//imshow("source", cameraFeed);//show cam feed
		
		waitKey(30);//delay 30ms
	}
	return 0;
}