#include <iostream>
#include <iomanip>
#include <vector>

#include "../core/types.hpp"
#include "convolution_io.hpp"

#include "delta_function_demo.hpp"


void delta_function_demo () {
    const convolution_t convolution(input_convolution(std::cin, std::cout));

    std::size_t sequence_length;
    std::cout << "Input sequence length: ";
    std::cin >> sequence_length;

    if (sequence_length % 2 == 0) {
        std::cout << "Sequence length should be odd" << std::endl;
        std::exit(1);
    }

    std::vector<double> delta_function(sequence_length, 0.);
    delta_function[sequence_length / 2] = 1.;

    std::cout << "Result: " << std::fixed << std::setprecision(10) << convolution(delta_function) << std::endl;
}
