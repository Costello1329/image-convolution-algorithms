#include <functional>
#include <numbers>
#include <cstddef>
#include <cmath>

#include "../core/utility.hpp"
#include "../core/types.hpp"

#include "discrete_convolution.hpp"


double integrate (
    const std::function<double(double)>& func,
    const double l,
    const double r,
    const std::size_t iterations_count
) {
    double res = 0.;

    for (std::size_t i = 0; i < iterations_count; i ++) {
        res += func(l + static_cast<double>(i) / static_cast<double>(iterations_count) * (r - l));
        res += func(l + static_cast<double>(i + 1) / static_cast<double>(iterations_count) * (r - l));
    }

    return res * (r - l) / static_cast<double>(iterations_count) / 2.;
}

sequence_t build_kernel (const double sigma) {
    static constinit std::size_t total_iterations_count = 1000000;

    std::function<double(double)> normal_distribution =
        [sigma] (const double x) -> double {
            return 1. / std::sqrt(2 * std::numbers::pi) / sigma * exp(- 1. / 2. * std::pow(x / sigma, 2.));
        };

    const std::size_t half_length = std::max<std::size_t>(static_cast<std::size_t>(8. * sigma), 1) / 2;
    const std::size_t length = half_length * 2 + 1;
    sequence_t kernel(length);

    for (std::size_t i = 0; i <= half_length; i ++) {
        const double l = - static_cast<double>(length) / 2. + static_cast<double>(i);
        const double r = l + 1.;
        kernel[length - 1 - i] = kernel[i] = integrate(normal_distribution, l, r, total_iterations_count / half_length);
    }

    return kernel;
}

sequence_t discrete_convolution (const sequence_t& sequence, const sequence_t& kernel) {
    sequence_t res(sequence.size(), 0.);

    for (std::size_t i = 0; i < sequence.size(); i ++)
        for (std::size_t j = 0; j < kernel.size(); j ++)
            res[i] += at_with_default(sequence, i + j - kernel.size() / 2) * kernel[j];

    return res;
}