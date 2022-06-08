#ifndef IMAGE_CONVOLUTIONS_ALGORITHMS_CONVOLUTIONS_DERICHE_CONVOLUTION_HPP
#define IMAGE_CONVOLUTIONS_ALGORITHMS_CONVOLUTIONS_DERICHE_CONVOLUTION_HPP

#include "../core/types.hpp"
#include "../convolutions/recursive_convolution.hpp"


convolution_t get_deriche_convolution (const gaussian_parameters_t& parameters);

gaussian_parameters_t gaussian_second_order (double sigma);
gaussian_parameters_t gaussian_fourth_order (double sigma);


#endif /// IMAGE_CONVOLUTIONS_ALGORITHMS_CONVOLUTIONS_DERICHE_CONVOLUTION_HPP.
