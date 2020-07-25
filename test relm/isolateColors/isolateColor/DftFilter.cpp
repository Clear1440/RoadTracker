#include "opencv2\opencv.hpp"
#include "DftFilter.h"

using namespace cv;
using namespace std;

void recenterDFT(Mat& source) {//used to show the dft in a way we can understand
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


void takeDFT(const Mat& source, Mat& destination) {
	Mat origionalComplex[2] = { source, Mat::zeros(source.size(), CV_32F) };
	Mat dftReady;

	merge(origionalComplex, 2, dftReady);

	Mat dftOfOrigional;

	dft(dftReady, dftOfOrigional, DFT_COMPLEX_OUTPUT);

	destination = dftOfOrigional;
}

void showDFT(const Mat& source) {
	Mat splitArray[2] = { Mat::zeros(source.size(), CV_32F) , Mat::zeros(source.size(), CV_32F) };
	split(source, splitArray);

	Mat dftMag;
	magnitude(splitArray[0], splitArray[1], dftMag);

	dftMag += Scalar::all(1);
	log(dftMag, dftMag);
	normalize(dftMag, dftMag, 0, 1, NORM_MINMAX);

	recenterDFT(dftMag);
	imshow("DFT", dftMag);
}

void invertDFT(const Mat& source, Mat& destination) {
	dft(source, destination, DFT_INVERSE | CV_HAL_DFT_REAL_OUTPUT | DFT_SCALE);
}


void lowPassDFTFilter(const Mat& source, Mat& destination) {
	Mat splitArray[2] = { Mat::zeros(source.size(), CV_32F) , Mat::zeros(source.size(), CV_32F) };

	split(source, splitArray);

	Mat dftMag;

	magnitude(splitArray[0], splitArray[1], dftMag);

	dftMag += Scalar::all(1);
	log(dftMag, dftMag);
	normalize(dftMag, dftMag, 0, 1, NORM_MINMAX);

	recenterDFT(dftMag);

	circle(dftMag, Point((dftMag.cols / 2), (dftMag.rows / 2)), 5, 0, FILLED);

	recenterDFT(dftMag);
	/*come back from freq*/
	imshow("lowpass", dftMag);


	idft(dftMag, dftMag);
	imshow("Reconstructed", dftMag);

	destination = dftMag;
}