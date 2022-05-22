#include <opencv2/opencv.hpp>
#include <type_traits>
#include <algorithm>
#include <concepts>
#include <utility>
#include <cstddef>
#include <vector>
#include <thread>

#include "convolution.h"

#include "utility.h"


cv::Mat convolve_one_axis (const cv::Mat& initial, const convolution_t& convolution, const bool horizontal_axis) {
    const auto pixel =
        [dir = horizontal_axis] <typename image_t> requires std::same_as<cv::Mat, std::remove_const_t<image_t>> (
            image_t& image, std::size_t k1, std::size_t k2, const std::size_t channel
        ) -> decltype(auto) {
            if (!dir)
            std::swap(k1, k2);

            return image.template at<uint8_t>(k1, 3 * k2 + channel);
        };

    const std::size_t h = initial.rows;
    const std::size_t w = initial.cols;

    cv::Mat img(initial.rows, initial.cols, CV_8UC3);
    const std::size_t dim1 = horizontal_axis ? h : w;
    const std::size_t dim2 = horizontal_axis ? w : h;

    std::vector<std::thread> threads;
    const std::size_t thread_cnt = std::min<std::size_t>(std::thread::hardware_concurrency(), dim1);

    for (std::size_t k = 0; k < thread_cnt; k ++) {
        const auto [block_start, block_size] = get_split_vector_block(dim1, thread_cnt, k);

        threads.emplace_back([
            l = block_start,
            r = block_start + block_size,
            dim2,
            &pixel,
            &initial,
            &img,
            &convolution
        ] () -> void {
            for (std::size_t channel = 0; channel < 3; channel ++)
                for (std::size_t k1 = l; k1 < r; k1 ++) {
                    sequence_t row(dim2);

                    for (std::size_t k2 = 0; k2 < dim2; k2++)
                        row[k2] = static_cast<double>(pixel(initial, k1, k2, channel));

                    row = convolution(row);

                    for (std::size_t k2 = 0; k2 < dim2; k2++)
                        pixel(img, k1, k2, channel) = static_cast<uint8_t>(row[k2]);
                }
        });
    }

    std::for_each(threads.begin(), threads.end(), [] (std::thread& thread) -> void { thread.join(); });
    return img;
}

cv::Mat convolve (const cv::Mat& initial, const convolution_t& convolution) {
    return convolve_one_axis(convolve_one_axis(initial, convolution, false), convolution, true);
}
