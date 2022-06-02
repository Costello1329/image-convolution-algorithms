# https://stackoverflow.com/questions/58404168/how-can-i-set-up-opencv-on-clion-for-mac

cmake_minimum_required(VERSION 3.22)
project(image_convolutions_algorithms)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 20)

add_executable(
    image_convolutions_algorithms
    main.cpp
    convolutions/recursive_convolution.hpp convolutions/recursive_convolution.cpp
    convolutions/discrete_convolution.hpp convolutions/discrete_convolution.cpp
    core/convolution.hpp core/convolution.cpp
    core/utility.hpp core/utility.cpp
    core/types.hpp
)

target_link_libraries(image_convolutions_algorithms ${OpenCV_LIBS})
