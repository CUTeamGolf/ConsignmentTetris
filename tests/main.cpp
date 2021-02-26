#define CATCH_CONFIG_MAIN
// TODO: check if this is supported by the Jenkins compiler
#if __has_include(<catch.hpp>)
# include <catch.hpp>
#else
# include "../externals/catch2/catch.hpp"
#endif

// find_all_maximum_rectangles tests
#include "process_optimiser_find_all_maximum_empty_rectangles.test.cc"
