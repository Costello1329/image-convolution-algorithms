#include <cstddef>
#include <numbers>
#include <cmath>

#include "../core/types.hpp"
#include "../core/utility.hpp"

#include "recursive_convolution.hpp"


sequence_t recursive_convolution (
    const sequence_t& sequence,
    const non_causal_coefficients_t& non_causal_coefficients,
    const double scale
) {
    const std::size_t l = sequence.size();
    const std::size_t depth = non_causal_coefficients.size();

    sequence_t y_plus(l, 0.);
    sequence_t y_minus(l, 0.);

    for (std::size_t i = 0; i < l; i ++)
        for (std::size_t j = 0; j < depth; j ++) {
            y_plus[i] += non_causal_coefficients[j][0] * at_with_default(sequence, i - j);
            y_plus[i] -= non_causal_coefficients[j][2] * at_with_default(y_plus, i - 1 - j);
        }

    for (std::size_t i = l - 1; i < l; i --)
        for (std::size_t j = 0; j < depth; j ++) {
            y_minus[i] += non_causal_coefficients[j][1] * at_with_default(sequence, i + 1 + j);
            y_minus[i] -= non_causal_coefficients[j][2] * at_with_default(y_minus, i + 1 + j);
        }

    sequence_t res(l, 0.);

    for (std::size_t i = 0; i < l; i ++)
        res[i] = scale * (y_plus[i] + y_minus[i]);

    return res;
}

non_causal_coefficients_t get_non_causal_coefficients (
        const causal_coefficients_t& causal_coefficients,
        const bool is_symmetric
) {
    const std::size_t depth = causal_coefficients.size();

    non_causal_coefficients_t result;
    result.reserve(causal_coefficients.size());

    for (std::size_t i = 0; i < depth; i ++) {
        const auto [n_i, d_i] = causal_coefficients[i];
        const double n_0 = causal_coefficients[0][0];
        const double n_i1 = (i < depth - 1 ? causal_coefficients[i + 1][0] : 0.);
        const double m_i = (is_symmetric ? 1. : -1.) * (n_i1 - d_i * n_0);
        result.push_back({ n_i, m_i, d_i });
    }

    return result;
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
