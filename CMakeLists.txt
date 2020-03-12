cmake_minimum_required(VERSION 3.14)
project(utils)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/lib)

include_directories(include)


add_executable(signed_int_to_binary_string signed_int_to_binary_string.cpp)