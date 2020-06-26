#include "hsvSearch.h"
#include "BWSearch.h"
#include "opencv2\opencv.hpp"
//#define isvideo 

using namespace cv;
using namespace std;


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
	Mat SamplePhoto;
#ifdef isvideo
	VideoCapture cap("sample3.mp4");
#endif // isvideo


	while (1) {
#ifdef isvideo
		cap >> SamplePhoto;
#else 
		SamplePhoto = imread("sample2.PNG", IMREAD_COLOR);//refresh
#endif // video
		//grayscaleFilter(SamplePhoto);
		HSVFilter(SamplePhoto);
	}
	return 0;
}

