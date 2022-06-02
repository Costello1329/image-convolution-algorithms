#ifndef IMAGE_CONVOLUTIONS_ALGORITHMS_CONVOLUTIONS_RECURSIVE_CONVOLUTION_HPP
#define IMAGE_CONVOLUTIONS_ALGORITHMS_CONVOLUTIONS_RECURSIVE_CONVOLUTION_HPP

#include <utility>
#include <vector>
#include <array>

#include "../core/types.hpp"


typedef std::vector<std::array<double, 2>> causal_coefficients_t;
typedef std::vector<std::array<double, 3>> non_causal_coefficients_t;

typedef std::pair<causal_coefficients_t, double> gaussian_parameters_t;

sequence_t recursive_convolution (
    const sequence_t& sequence,
    const non_causal_coefficients_t& non_causal_coefficients,
    double scale
);

non_causal_coefficients_t get_non_causal_coefficients (
    const causal_coefficients_t& causal_coefficients,
    bool is_symmetric
);

gaussian_parameters_t gaussian_fourth_order (double sigma);
gaussian_parameters_t gaussian_second_order (double sigma);


#endif /// IMAGE_CONVOLUTIONS_ALGORITHMS_CONVOLUTIONS_RECURSIVE_CONVOLUTION_HPP.
