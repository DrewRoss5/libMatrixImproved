cmake_minimum_required(VERSION 3.28)

project(libMatrix VERSION 0.1.0)

include_directories("inc")

add_library(matrixlib STATIC src/matrix.cpp inc/matrix.h)

# this is for ad-hoc testing before a test suite is written
add_executable(main src/main.cpp src/matrix.cpp inc/matrix.h)