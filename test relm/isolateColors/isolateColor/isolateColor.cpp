#include <iostream>
#include "opencv2\opencv.hpp"
#include <stdint.h>

using namespace cv;
using namespace std;

void takeDFT(const Mat& source, Mat& destination);
void recenterDFT(Mat& source);


void takeDFT(const Mat& source, Mat& destination) {
	Mat origionalComplex[2] = { source, Mat::zeros(source.size(), CV_32F) };

	Mat dftReady;

	merge(origionalComplex, 2, dftReady);

	Mat dftOfOrigional;

	dft(dftReady, dftOfOrigional, DFT_COMPLEX_OUTPUT);

	destination = dftOfOrigional;
}

void revDFT(const Mat& source, Mat& destination) {
	Mat origionalComplex[2] = { source, Mat::zeros(source.size(), CV_32F) };

	Mat dftReady;

	merge(origionalComplex, 2, dftReady);

	Mat dftOfOrigional;

	dft(dftReady, dftOfOrigional, DFT_COMPLEX_OUTPUT | DFT_INVERSE);

	destination = dftOfOrigional;
}


void showDFT(const Mat& source) {
	Mat splitArray[2] = { Mat::zeros(source.size(), CV_32F) , Mat::zeros(source.size(), CV_32F) };

	split(source, splitArray);

	Mat dftMag;

	magnitude( splitArray[0], splitArray[1], dftMag );

	dftMag += Scalar::all(1);
	log(dftMag, dftMag);

	normalize(dftMag, dftMag, 0, 1, NORM_MINMAX);

	/*
	for (int i = 0; i < dftMag.rows/24; i++) {
		for (int j = 0; j < dftMag.cols; j++) {
			dftMag.at<float>(i, j) = 0;
			dftMag.at<float>((dftMag.rows-1) - i, (dftMag.cols-1) - j) = 0;
		}
	}
	*/

	recenterDFT(dftMag);
	imshow("DFT", dftMag);
}

void showDFTrev(const Mat& source) {
	Mat splitArray[2] = { Mat::zeros(source.size(), CV_32F) , Mat::zeros(source.size(), CV_32F) };

	split(source, splitArray);

	Mat dftMag;

	magnitude(splitArray[0], splitArray[1], dftMag);

	dftMag += Scalar::all(1);
	log(dftMag, dftMag);

	normalize(dftMag, dftMag, 0, 1, NORM_MINMAX);
	recenterDFT(dftMag);
	imshow("DFT_rev", dftMag);
}

void invertDFT(const Mat& source, Mat& destination) {
	dft(source, destination, DFT_INVERSE | CV_HAL_DFT_REAL_OUTPUT | DFT_SCALE);
}

void recenterDFT(Mat& source) {
	int centerx = source.cols / 2;
	int centery = source.rows / 2;

	Mat q1(source, Rect(0, 0, centerx, centery));
	Mat q2(source, Rect(centerx, 0, centerx, centery));
	Mat q3(source, Rect(0, centery, centerx, centery));
	Mat q4(source, Rect(centerx, centery, centerx, centery));

	Mat swapMap;

	q1.copyTo(swapMap);
	q4.copyTo(q1);
	swapMap.copyTo(q4);

	q2.copyTo(swapMap);
	q3.copyTo(q2);
	swapMap.copyTo(q3);
}

int main() {
	Mat cameraFeed, cameraFeedGray;
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

		revDFT(dftOfOrigional, dftOfOrigional);
		showDFTrev(dftOfOrigional);

		imshow("source", cameraFeed);//show cam feed
		imshow("Original Image gray", cameraFeedGray);//show cam feed
		
		waitKey(30);//delay 30ms
	}
	return 0;
}