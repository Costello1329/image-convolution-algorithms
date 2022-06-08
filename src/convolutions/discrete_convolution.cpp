#include <functional>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cstddef>
#include <cmath>

#include "../core/utility.hpp"
#include "../core/types.hpp"

#include "discrete_convolution.hpp"


sequence_t gaussian_kernel (const double sigma) {
    std::function<double(double)> normal_distribution =
        [sigma] (const double x) -> double {
            return 1. / std::sqrt(2 * std::numbers::pi) / sigma * exp(- 1. / 2. * std::pow(x / sigma, 2.));
        };

    const std::size_t half_length = std::max<std::size_t>(static_cast<std::size_t>(8. * sigma), 1) / 2;
    const std::size_t length = half_length * 2 + 1;
    sequence_t kernel(length);

    for (std::size_t i = 0; i <= half_length; i ++)
        kernel[half_length - i] = kernel[half_length + i] = normal_distribution(static_cast<double>(i));

    const double norm = std::accumulate(kernel.cbegin(), kernel.cend(), 0.);
    sequence_t normalised_kernel;
    normalised_kernel.reserve(length);
    std::transform(
        kernel.cbegin(),
        kernel.cend(),
        std::back_inserter(normalised_kernel),
        [norm] (const double el) { return el / norm; }
    );
    return normalised_kernel;
}

sequence_t discrete_convolution (const sequence_t& sequence, const sequence_t& kernel) {
    sequence_t res(sequence.size(), 0.);

    for (std::size_t i = 0; i < sequence.size(); i ++)
        for (std::size_t j = 0; j < kernel.size(); j ++)
            res[i] += at_with_default(sequence, i + j - kernel.size() / 2) * kernel[j];

    return res;
}

convolution_t get_discrete_convolution (const sequence_t& kernel) {
    return [kernel] (const sequence_t& sequence) -> sequence_t {
        return discrete_convolution(sequence, kernel);
    };
}
