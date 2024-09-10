cmake_minimum_required(VERSION 3.28)

project(libMatrix VERSION 0.1.0)

include_directories("inc")

add_library(matrixlib STATIC src/matrix.cpp inc/matrix.h)

find_package(GTest)
include(GoogleTest)
add_executable(tests
               test/main_test.cpp
               inc/matrix.h
               src/matrix.cpp)  
target_link_libraries(tests PRIVATE GTest::gtest)