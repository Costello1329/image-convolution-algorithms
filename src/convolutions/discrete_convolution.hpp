#ifndef IMAGE_CONVOLUTIONS_ALGORITHMS_DISCRETE_CONVOLUTION_HPP
#define IMAGE_CONVOLUTIONS_ALGORITHMS_DISCRETE_CONVOLUTION_HPP

#include "../core/types.hpp"


sequence_t gaussian_kernel (double sigma);
convolution_t get_discrete_convolution (const sequence_t& sequence);


#endif /// IMAGE_CONVOLUTIONS_ALGORITHMS_DISCRETE_CONVOLUTION_HPP.
