# BDSP unit tests CMakeLists.txt

cmake_minimum_required(VERSION 3.15)

project(bdsp_tests VERSION 0.1.0)

add_subdirectory(Catch2)                  

set(SRC_TESTS 
    source/test_tests.cpp
    source/test_decibel.cpp
    source/test_util.cpp
    source/test_mappings.cpp)

set(SRC_BENCHMARKS )

add_executable(bdsp_tests
    ${SRC_TESTS}
    ${SRC_BENCHMARKS})

target_link_libraries(bdsp_tests 
    PRIVATE
        Catch2::Catch2WithMain)