#define GET_FULL_PROCESS_OPTIMISER_HEADER
#if __has_include("process_optimiser.h")
# include "process_optimiser.h"
#else
# include "../src/process_optimiser.h"
#endif

TEST_CASE( "find_all_maximum_empty_cuboids: no MECs found when whole box filled ") {
    // big cuboi
    Cuboid c = {0, 0, 0, 10, 10, 10};

    std::vector<Cuboid> cubes = {c};

    std::vector<MaximumEmptyCuboid> results =
        find_all_maximum_empty_cuboids<10, 10>(cubes, 10);

    REQUIRE( results.size() == 0 );
}

TEST_CASE( "find_all_maximum_empty_cuboids: one MEC found when only room for one ") {
    // two tall cuboids
    Cuboid c1 = {0, 0, 0, 10, 6, 10};
    Cuboid c2 = {0, 7, 0, 10, 3, 10};

    std::vector<Cuboid> cubes = {c1, c2};

    std::vector<MaximumEmptyCuboid> results =
        find_all_maximum_empty_cuboids<10, 10>(cubes, 10);

    REQUIRE( results.size() == 1 );
    REQUIRE( results[0].x == 0 );
    REQUIRE( results[0].y == 6 );
    REQUIRE( results[0].z == 0 );
    REQUIRE( results[0].length == 10 );
    REQUIRE( results[0].width == 1 );
    REQUIRE( results[0].height == 10 );
}
