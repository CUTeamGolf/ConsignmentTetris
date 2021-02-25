cmake_minimum_required(VERSION 3.4)
project(process_optimiser)

include(CTest)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src)
add_subdirectory(tests)