#define GET_FULL_PROCESS_OPTIMISER_HEADER
#if __has_include("process_optimiser.h")
# include "process_optimiser.h"
#else
# include "../src/process_optimiser.h"
#endif

bool has_MEC_utility(const Cuboid & box, const std::vector<MaximumEmptyCuboid> &cubes) {
    for (auto c : cubes) {
        if (c.x == box.x && c.y == box.y && c.z == box.z &&
                c.length == box.length && c.width == box.width && c.height == box.height) {
            return true;
        }
    }
    return false;
}

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

TEST_CASE( "find_all_maximum_empty_cuboids: five MECs found when small box in centre at floor" ) {
    // one small cuboid
    Cuboid c1 = {3, 2, 0, 3, 3, 5};

    std::vector<Cuboid> cubes = {c1};

    std::vector<MaximumEmptyCuboid> results =
        find_all_maximum_empty_cuboids<10, 10>(cubes, 10);

    // the expected MECs
    Cuboid expected[5] = {
        {0, 0, 0, 3, 10, 10},
        {0, 0, 0, 10, 2, 10},
        {6, 0, 0, 4, 10, 10},
        {0, 5, 0, 10, 5, 10},
        {0, 0, 5, 10, 10, 5}
    };

    REQUIRE( results.size() == 5 );
    REQUIRE( has_MEC_utility(expected[0], results));
    REQUIRE( has_MEC_utility(expected[1], results));
    REQUIRE( has_MEC_utility(expected[2], results));
    REQUIRE( has_MEC_utility(expected[3], results));
    REQUIRE( has_MEC_utility(expected[4], results));
}

TEST_CASE( "find_all_maximum_empty_cuboids: five MECs found when small box in hovering ") {
    // one small cuboid
    Cuboid c1 = {3, 2, 2, 3, 3, 5};

    std::vector<Cuboid> cubes = {c1};

    std::vector<MaximumEmptyCuboid> results =
        find_all_maximum_empty_cuboids<10, 10>(cubes, 10);

    // the expected MECs
    Cuboid expected[5] = {
        {0, 0, 0, 3, 10, 10},
        {0, 0, 0, 10, 2, 10},
        {6, 0, 0, 4, 10, 10},
        {0, 5, 0, 10, 5, 10},
        {0, 0, 7, 10, 10, 3}
    };

    REQUIRE( results.size() == 5 );
    REQUIRE( has_MEC_utility(expected[0], results));
    REQUIRE( has_MEC_utility(expected[1], results));
    REQUIRE( has_MEC_utility(expected[2], results));
    REQUIRE( has_MEC_utility(expected[3], results));
    REQUIRE( has_MEC_utility(expected[4], results));
}

TEST_CASE( "find_all_maximum_empty_cuboids: three MECs found when small box in corner" ) {
    // one small cuboid
    Cuboid c1 = {0, 0, 0, 3, 4, 5};

    std::vector<Cuboid> cubes = {c1};

    std::vector<MaximumEmptyCuboid> results =
        find_all_maximum_empty_cuboids<10, 10>(cubes, 10);

    // the expected MECs
    Cuboid expected[5] = {
        {3, 0, 0, 7, 10, 10},
        {0, 4, 0, 10, 6, 10},
        {0, 0, 5, 10, 10, 5}
    };

    REQUIRE( results.size() == 3 );
    REQUIRE( has_MEC_utility(expected[0], results));
    REQUIRE( has_MEC_utility(expected[1], results));
    REQUIRE( has_MEC_utility(expected[2], results));
}
