#include <algorithm>
#include <utility>
#include <cstddef>

#include "utility.hpp"


std::pair<std::size_t, std::size_t> get_split_vector_block (
    const std::size_t size,
    const std::size_t blocks_cnt,
    const std::size_t block_idx
) {
    const std::size_t base_block_size = size / blocks_cnt;
    const std::size_t long_block_cnt = size % blocks_cnt;

    return {
        base_block_size * block_idx + std::min<std::size_t>(block_idx, long_block_cnt),
        base_block_size + static_cast<std::size_t>(block_idx < long_block_cnt)
    };
}
