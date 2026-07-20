#pragma once
#include <string>

struct AsiROI;
bool isAligned(const cv::Mat& img, const AsiROI& roiInfo);