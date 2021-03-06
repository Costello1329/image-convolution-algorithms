#ifndef IMAGE_CONVOLUTIONS_ALGORITHMS_CORE_TYPES_HP
#define IMAGE_CONVOLUTIONS_ALGORITHMS_CORE_TYPES_HP

#include <functional>
#include <vector>


typedef std::vector<double> sequence_t;
typedef std::function<sequence_t(sequence_t)> convolution_t;


#endif /// IMAGE_CONVOLUTIONS_ALGORITHMS_CORE_TYPES_HP.
