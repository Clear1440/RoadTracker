#pragma once
#include "opencv2/opencv.hpp"

void createTrackbarsBW(int& BW_MIN, int& BW_MAX);
void grayscaleFilter(cv::Mat& Src);