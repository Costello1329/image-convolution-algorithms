#ifndef IMAGE_CONVOLUTIONS_ALGORITHMS_CONVOLUTION_HPP
#define IMAGE_CONVOLUTIONS_ALGORITHMS_CONVOLUTION_HPP

#include <opencv2/opencv.hpp>

#include "types.hpp"


cv::Mat convolve (const cv::Mat& initial, const convolution_t& convolution);


#endif /// IMAGE_CONVOLUTIONS_ALGORITHMS_CONVOLUTION_HPP.
