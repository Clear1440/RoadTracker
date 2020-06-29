#include "opencv2\opencv.hpp"

void takeDFT(const cv::Mat& source, cv::Mat& destination);
void showDFT(const cv::Mat& source);
void invertDFT(const cv::Mat& source, cv::Mat& destination);
void recenterDFT(cv::Mat& source);
void lowPassDFTFilter(const cv::Mat& source, cv::Mat& destination);