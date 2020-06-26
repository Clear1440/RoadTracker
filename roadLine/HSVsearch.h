#include <string.h>
#include <iostream>
#include <sstream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
#include <opencv2\imgproc.hpp>

using namespace cv;
using namespace std;


void createTrackbarsHSV(int& H_MIN, int& H_MAX, int& S_MIN, int& S_MAX, int& V_MIN, int& V_MAX);
void morphOps(Mat&);
void on_trackbar(int, void*);
void drawCenterLine(const Mat, Mat&);
void maskThreshold(Mat&);
