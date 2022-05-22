#ifndef IMAGE_CONVOLUTIONS_ALGORITHMS_CORE_UTILITY_H
#define IMAGE_CONVOLUTIONS_ALGORITHMS_CORE_UTILITY_H

#include <stdexcept>
#include <cstddef>
#include <utility>


std::pair<std::size_t, std::size_t> get_split_vector_block (
    std::size_t size,
    std::size_t blocks_cnt,
    std::size_t block_idx
);

template <typename vt>
vt at_with_default (const std::vector<vt>& vec, const std::size_t idx) {
    try { return vec.at(idx); }
    catch (const std::out_of_range& ignored) { return vt(); }
}


#endif /// IMAGE_CONVOLUTIONS_ALGORITHMS_CORE_UTILITY_H.
