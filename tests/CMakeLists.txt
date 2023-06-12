# BDSP unit tests CMakeLists.txt

cmake_minimum_required(VERSION 3.15)

project(bdsp_tests VERSION 0.1.0)

add_subdirectory(Catch2)                  

set(SRC_TESTS 
    source/test_tests.cpp
    source/test_decibel.cpp
    source/test_util.cpp)

add_executable(bdsp_tests
    ${SRC_TESTS})

target_link_libraries(bdsp_tests 
    PRIVATE
        Catch2::Catch2WithMain)