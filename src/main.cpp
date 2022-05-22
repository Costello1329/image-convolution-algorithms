#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>

#include "convolutions/recursive_convolution.h"
#include "convolutions/discrete_convolution.h"
#include "core/convolution.h"
#include "core/types.h"


convolution_t get_deriche_convolution (const gaussian_parameters_t& parameters) {
    const auto [causal_coefficients, scale] = parameters;

    return [
        non_causal_coefficients = get_non_causal_coefficients(causal_coefficients, true),
        scale = scale
    ] (const sequence_t &sequence) -> sequence_t {
        return recursive_convolution(sequence, non_causal_coefficients, scale);
    };
}

convolution_t get_convolution_by_type_and_sigma (const std::string& type, const double sigma) {
    if (type == "discrete")
        return [kernel = build_kernel(sigma)] (const sequence_t& sequence) -> sequence_t {
            return discrete_convolution(sequence, kernel);
        };

    else if (type == "deriche2")
        return get_deriche_convolution(gaussian_second_order(sigma));

    else if (type == "deriche4")
        return get_deriche_convolution(gaussian_fourth_order(sigma));

    else {
        std::cout << "Wrong convolution type" << std::endl;
        std::exit(1);
    }
}

std::string get_img_path (const std::string& src_path, const std::string& type) {
    const std::size_t dot_idx = src_path.rfind('.');
    std::string suffix;

    if (type == "discrete") suffix = "d";
    else if (type == "deriche2") suffix = "d2";
    else if (type == "deriche4") suffix = "d4";
    else {
        std::cout << "Wrong convolution type" << std::endl;
        std::exit(1);
    }

    return src_path.substr(0, dot_idx) + "_" + suffix + src_path.substr(dot_idx, std::string::npos);
}


int main () {
    std::cout << "Input convolution type [discrete, deriche2, or deriche4]: ";

    std::string type;
    std::cin >> type;

    double sigma;
    std::cout << "Input sigma: ";
    std::cin >> sigma;

    /// EXAMPLE: /Users/Costello1329/Desktop/img.png
    std::string src_path;
    std::cout << "Input source path: ";
    std::cin >> src_path;
    const cv::Mat src = cv::imread(src_path);

    const std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    cv::Mat res = convolve(src, get_convolution_by_type_and_sigma(type, sigma));
    const std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    const std::size_t difference = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    std::cout << "Performed in " << difference << "ms" << std::endl;

    cv::imshow(type + " convolution result", res);
    cv::waitKey(0);

    cv::imwrite(get_img_path(src_path, type), res);

    return 0;
}
