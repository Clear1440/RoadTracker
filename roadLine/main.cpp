#include "HSVsearch.hpp"
#include "BWSearch.hpp"
#include "CannySearch.hpp"
#include "opencv2/opencv.hpp"

//#define isvideo 

using namespace cv;
using namespace std;


int main(int argc, char* argv[]) {
	Mat src;
#ifdef isvideo
	VideoCapture cap("./examples/vids/sample.mp4");
#endif // isvideo

	while (1) {
		/* src input*/
#ifdef isvideo
		cap >> src;
#else 
		src = imread("./examples/pics/sample.PNG", IMREAD_COLOR);//refresh
#endif // video

		/* Filtering done down here*/
		//cannyFilter(src);
		//waitKey(1);//required for Canny

		grayscaleFilter(src);
		//HSVFilter(src);

	}
	return 0;
}

