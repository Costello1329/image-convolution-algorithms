#include <cstddef>

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
        const double n_i_next = (i < depth - 1 ? causal_coefficients[i + 1][0] : 0.);
        const double m_i = (is_symmetric ? 1. : -1.) * (n_i_next - d_i * n_0);
        result.push_back({ n_i, m_i, d_i });
    }

    return result;
}
