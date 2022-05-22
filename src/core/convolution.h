#ifndef IMAGE_CONVOLUTIONS_ALGORITHMS_CONVOLUTION_H
#define IMAGE_CONVOLUTIONS_ALGORITHMS_CONVOLUTION_H

#include <opencv2/opencv.hpp>

#include "types.h"


cv::Mat convolve (const cv::Mat& initial, const convolution_t& convolution);


#endif /// IMAGE_CONVOLUTIONS_ALGORITHMS_CONVOLUTION_H.
