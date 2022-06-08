#ifndef IMAGE_CONVOLUTIONS_ALGORITHMS_DEMO_CONVOLUTION_IO_HPP
#define IMAGE_CONVOLUTIONS_ALGORITHMS_DEMO_CONVOLUTION_IO_HPP

#include <iostream>
#include <numeric>

#include "../core/types.hpp"


convolution_t input_convolution (std::istream& is, std::ostream& os);

std::ostream& operator<< (std::ostream& os, const sequence_t& sequence);


#endif /// IMAGE_CONVOLUTIONS_ALGORITHMS_DEMO_CONVOLUTION_IO_HPP.
