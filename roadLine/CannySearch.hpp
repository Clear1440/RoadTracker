#pragma once
#include "opencv2/opencv.hpp"

void createTrackbarsCanny(int& Canny_MIN);
void cannyFilter(cv::Mat& src);