cmake_minimum_required(VERSION 3.17)
project(src)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME process_optimiser)

add_executable(src process_optimiser.cc)

add_library(${TARGET_NAME}
  process_optimiser.cc
  process_optimiser.h)
 
target_include_directories(${TARGET_NAME}
  INTERFACE ./)
 
install(TARGETS ${TARGET_NAME}
  ARCHIVE DESTINATION lib/)