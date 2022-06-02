#ifndef IMAGE_CONVOLUTIONS_ALGORITHMS_DISCRETE_CONVOLUTION_HPP
#define IMAGE_CONVOLUTIONS_ALGORITHMS_DISCRETE_CONVOLUTION_HPP

#include "../core/types.hpp"


sequence_t build_kernel (double sigma);
sequence_t discrete_convolution (const sequence_t& sequence, const sequence_t& kernel);


#endif /// IMAGE_CONVOLUTIONS_ALGORITHMS_DISCRETE_CONVOLUTION_HPP.
