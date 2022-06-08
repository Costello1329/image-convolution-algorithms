#include <iostream>

#include "demo/convolution_demo.hpp"
#include "demo/delta_function_demo.hpp"


int main () {
    std::size_t demo;
    std::cout << "Choose demo [1 for image smoothing and 2 for delta function convolution]: ";
    std::cin >> demo;

    switch (demo) {
        case 1:
            convolve_demo();
            break;
        case 2:
            delta_function_demo();
            break;
        default:
            break;
    }

    return 0;
}
