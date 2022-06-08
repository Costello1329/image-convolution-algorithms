#include <iostream>

#include "../core/types.hpp"
#include "../convolutions/discrete_convolution.hpp"
#include "../convolutions/deriche_convolution.hpp"

#include "convolution_io.hpp"


convolution_t get_convolution_by_type_and_sigma (const std::string& type, const double sigma, std::ostream& os) {
    if (type == "discrete")
        return get_discrete_convolution(gaussian_kernel(sigma));

    else if (type == "deriche2")
        return get_deriche_convolution(gaussian_second_order(sigma));

    else if (type == "deriche4")
        return get_deriche_convolution(gaussian_fourth_order(sigma));

    else {
        os << "Wrong convolution type" << std::endl;
        std::exit(1);
    }
}

convolution_t input_convolution (std::istream& is, std::ostream& os) {
    os << "Input convolution type [discrete, deriche2, or deriche4]: ";
    std::string type;
    is >> type;

    os << "Input sigma: ";
    double sigma;
    is >> sigma;

    return get_convolution_by_type_and_sigma(type, sigma, os);
}
