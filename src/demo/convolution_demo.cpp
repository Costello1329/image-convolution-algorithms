#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <chrono>

#include "../core/types.hpp"
#include "../core/convolution.hpp"
#include "convolution_io.hpp"

#include "convolution_demo.hpp"


std::string get_res_img_path (const std::string& src_path) {
    const std::size_t dot_idx = src_path.rfind('.');
    return src_path.substr(0, dot_idx).append("_res").append(src_path.substr(dot_idx, std::string::npos));
}

void convolve_demo () {
    const convolution_t convolution(input_convolution(std::cin, std::cout));

    /// EXAMPLE: /Users/Costello1329/Desktop/img.png
    std::string src_path;
    std::cout << "Input source path: ";
    std::cin >> src_path;
    const cv::Mat src = cv::imread(src_path);

    const std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    cv::Mat res = convolve(src, convolution);
    const std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    const std::size_t difference = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    std::cout << "Performed in " << difference << "ms" << std::endl;

    cv::imshow("convolution result", res);
    cv::waitKey(0);

    cv::imwrite(get_res_img_path(src_path), res);
}

std::ostream& operator<< (std::ostream& os, const sequence_t& sequence) {
    os << "[";
    std::for_each(
        sequence.cbegin(),
        sequence.cend(),
        [&os, is_first = true] (const double el) mutable {
            os << (!is_first ? ", " : "") << el;
            is_first = false;
        }
    );
    os << "]";
    return os;
}

