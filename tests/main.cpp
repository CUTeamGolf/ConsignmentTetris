#define GET_FULL_PROCESS_OPTIMISER_HEADER
#define CATCH_CONFIG_MAIN
#if __has_include(<catch.hpp>)
# include <catch.hpp>
#else
# include "../externals/catch2/catch.hpp"
#endif

// BoxTetromino tests
#include "process_optimiser_box_tetromino.test.cc"

// find_all_maximum_rectangles tests
#include "process_optimiser_find_all_maximum_empty_rectangles.test.cc"

// find_all_maximum_empty_cuboids tests
#include "process_optimiser_find_all_maximum_empty_cuboids.test.cc"

// process_optimiser_main tests
#include "process_optimiser_main_driver.test.cc"
