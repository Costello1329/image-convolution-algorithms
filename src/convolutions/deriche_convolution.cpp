#include <numbers>
#include <cmath>

#include "../convolutions/recursive_convolution.hpp"

#include "deriche_convolution.hpp"


convolution_t get_deriche_convolution (const gaussian_parameters_t& parameters) {
    const auto [causal_coefficients, scale] = parameters;

    return [
        non_causal_coefficients = get_non_causal_coefficients(causal_coefficients, true),
        scale = scale
    ] (const sequence_t &sequence) -> sequence_t {
        return recursive_convolution(sequence, non_causal_coefficients, scale);
    };
}

gaussian_parameters_t gaussian_second_order (const double sigma) {
    const double alpha = 5. / 2. / std::sqrt(std::numbers::pi) / sigma;

    const double e = std::exp(-alpha);
    const double e2 = std::exp(-2. * alpha);
    const double k = std::pow(1. - e, 2.) / (1. + 2. * alpha * e - e2);

    return { { { k, - 2. * e }, { k * e * (alpha - 1), e2 } }, 1. };
}

gaussian_parameters_t gaussian_fourth_order (const double sigma) {
    const double a1 = 1.680;
    const double a2 = -0.6803;
    const double b1 = 3.735;
    const double b2 = -0.2598;
    const double w1 = 0.6318;
    const double w2 = 1.997;
    const double l1 = -1.783;
    const double l2 = -1.723;

    const auto e = [sigma, l1, l2] (const double k1, const double k2) -> double {
        return std::exp((k1 * l1 + k2 * l2) / sigma);
    };

    const double e10 = e(1., 0.);
    const double e01 = e(0., 1.);
    const double e11 = e(1., 1.);
    const double e20 = e(2., 0.);
    const double e21 = e(2., 1.);
    const double e02 = e(0., 2.);
    const double e12 = e(1., 2.);
    const double e22 = e(2., 2.);

    const double sin1 = std::sin(w1 / sigma);
    const double sin2 = std::sin(w2 / sigma);
    const double cos1 = std::cos(w1 / sigma);
    const double cos2 = std::cos(w2 / sigma);

    const double n0 = a1 + a2;
    const double n1 = e10 * (b1 * sin1 - (a1 + 2. * a2) * cos1) + e01 * (b2 * sin2 - (2. * a1 + a2) * cos2);
    const double n2 = 2. * e11 * ((a1 + a2) * cos1 * cos2 - b1 * sin1 * cos2 - b2 * cos1 * sin2) + a1 * e02 + a2 * e20;
    const double n3 = e21 * (b2 * sin2 - a2 * cos2) + e12 * (b1 * sin1 - a1 * cos1);

    const double d1 = -2. * (e01 * cos1 + e10 * cos2);
    const double d2 = 4. * e11 * cos1 * cos2 + e20 + e02;
    const double d3 = -2. * (e12 * cos1 + e21 * cos2);
    const double d4 = e22;

    const double scale = 1. / (2. * (n0 + n1 + n2 + n3) / (1. + d1 + d2 + d3 + d4) - n0);

    return { { { n0, d1 }, { n1, d2 }, { n2, d3 }, { n3, d4 } }, scale };
}
