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
    convolutions/recursive_convolution.h convolutions/recursive_convolution.cpp
    convolutions/discrete_convolution.h convolutions/discrete_convolution.cpp
    core/convolution.h core/convolution.cpp
    core/utility.h core/utility.cpp
    core/convolution.h core/convolution.cpp
    core/types.h
)

target_link_libraries(image_convolutions_algorithms ${OpenCV_LIBS})
