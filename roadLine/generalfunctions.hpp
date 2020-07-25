#pragma once
#include <string.h>
#include <iostream>
#include <sstream>
#include "opencv2/opencv.hpp"

void drawCenterLine(const cv::Mat thresh, cv::Mat& drawOn, int widthOfLine = 4);
void morphOps(cv::Mat& thresh);
void maskThreshold(cv::Mat& thresh);