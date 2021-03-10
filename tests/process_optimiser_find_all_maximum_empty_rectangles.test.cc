#define GET_FULL_PROCESS_OPTIMISER_HEADER
#if __has_include("process_optimiser.h")
# include "process_optimiser.h"
#else
# include "../src/process_optimiser.h"
#endif

// helper method for checking if the result contains a specific rectangle
bool contains_rectangle(const std::vector<MaximumEmptyRectangle>& results, const MaximumEmptyRectangle& rec) {
    for (auto & r : results) {
        if (r.llx == rec.llx &&
                r.lly == rec.lly &&
                r.urx == rec.urx &&
                r.ury == rec.ury) {
            return true;
        }
    }
    return false;
}

TEST_CASE( "find_all_maximum_empty_rectangles: example 1 works ") {
    // --x-
    // --xx
    // --xx
    // --x-
    bool occupied[4][4] = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {1, 0, 0, 1}
    };

    std::vector<MaximumEmptyRectangle> rects =
        find_all_maximum_empty_rectangles<4, 4>(occupied);

    // we expect the following rectangles
    // NOTE that the ur corner is non-inclusive ends
    MaximumEmptyRectangle mer1 = {2, 0, 3, 4};
    MaximumEmptyRectangle mer2 = {2, 1, 4, 3};

    REQUIRE (rects.size() == 2 );
    REQUIRE ( contains_rectangle(rects, mer1) );
    REQUIRE ( contains_rectangle(rects, mer2) );
}

TEST_CASE( "find_all_maximum_empty_rectangles: example 2 works") {
    // 00
    // 00
    bool occupied[2][2] = {
        {0, 0},
        {0, 0}
    };

    std::vector<MaximumEmptyRectangle> rects = find_all_maximum_empty_rectangles<2, 2>(occupied);

    MaximumEmptyRectangle expected_mers[1] = {
        {0, 0, 2, 2}
    };

    int expected_sols = sizeof(expected_mers) / sizeof(MaximumEmptyRectangle);

    REQUIRE(rects.size() == expected_sols);
    for (int i = 0; i < expected_sols; i++) {
        REQUIRE( contains_rectangle(rects, expected_mers[i]) );
    }
}

TEST_CASE ( "find_all_maximum_empty_rectangles: example 3 works ") {
    // 01110111111111101111011111010111110111001101111111
    // 11111111111111111111111110101110111101110101001110
    // 01111001111111111011111111111011101111101011111111
    // 01011111101011111011100111011111111100111001111111
    // 11111100110111101111011100101111111101110010111101
    // 11011110111101101011111111111111001111010011001000
    // 11111011111110111101011110110111111111100111111111
    // 11111011111011101001111111110101110100101101111111
    // 01111111111111011111011111111010111111111011110111
    // 01111011111000101101110010111111110111111111111110
    // 11111111110111111111010111100111100011011101111101
    // 01111111111011111001110010101111111101111110111111
    // 01111101110111111111101011111010110111101011111110
    // 11101110011111111111111111111111111111111111111110
    // 11100011111111110100101110111111011101111111111110
    // 11110111111011111111101111111111111111111110110101
    // 11111111011111011111101011001111111111111111111001
    // 11111111111010111001111111001011110111111111001111
    // 11111111110011111110111111111011111110101111011111
    // 10010111111100111110111111101111011111100111000111
    // 01111011111111011111101011010110111101110111101111
    // 01100111101111111011111111111111111111011010011111
    // 11111111111111111100111011110110000011111011111001
    // 11101101111101111101111111111111110011101111111111
    // 11011111011111111111011011111111101101011111111110
    // 11011101111111011101111111011001111110011111110111
    // 11111111101111011111111111111110011001110011111111
    // 11100011111111111111000101101111111110110111011101
    // 11011101011011101111111111111011111111111111110011
    // 01011111111111111111101111101110111100101111111111
    // 11111001111110110010101111101111111011111111101111
    // 11101011111111111111111111100111111111111110111010
    // 11110101110001110111111101110101111111001110111111
    // 11011111100001101110111110111110001101011001111111
    // 11111111111110100111111000111101111111110011111111
    // 10101011110111111111101111111101111101111111110110
    // 11111111011111111011101111111101111111111011111111
    // 11101111101001111111011111110110011110001111101110
    // 10001111111111111001111110111011111011111011111110
    // 11101111111001101110111111111111110111111111111111
    // 11011111111111111101101111110011111110111110111111
    // 01011100000011111100110101110111111111111101111111
    // 11111101111111101111011111111111111110011111111101
    // 11010111111111110011111111100101111111011111111011
    // 11111101011111111100011111111111110111111111111110
    // 11111111100101110111111000011011011101111111111011
    // 11011111110111111111110000111001101101110111011101
    // 11111110111111010001111111111010101011111110111011
    // 10000111111011111111011100110110110101111110111111
    // 11111111111011101001101111111101111011011011011101
    bool occupied[50][50] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1},
        {1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0},
        {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1},
        {0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0},
        {1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0},
        {1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1}
    };

    std::vector<MaximumEmptyRectangle> rects = find_all_maximum_empty_rectangles<50, 50>(occupied);

    MaximumEmptyRectangle expected_mers[345] = {
        {0, 8, 1, 9},
        {0, 20, 1, 21},
        {0, 28, 1, 30},
        {0, 37, 1, 39},
        {0, 40, 1, 42},
        {0, 46, 1, 48},
        {0, 49, 1, 50},
        {1, 1, 5, 2},
        {1, 11, 4, 12},
        {1, 14, 2, 15},
        {1, 30, 3, 31},
        {2, 3, 3, 4},
        {2, 6, 3, 7},
        {2, 8, 3, 10},
        {2, 16, 3, 17},
        {2, 20, 3, 22},
        {2, 24, 3, 26},
        {2, 44, 3, 45},
        {2, 46, 3, 47},
        {3, 10, 4, 13},
        {3, 14, 4, 15},
        {3, 18, 4, 19},
        {3, 22, 6, 23},
        {3, 26, 4, 27},
        {3, 28, 5, 29},
        {3, 35, 4, 37},
        {3, 35, 6, 36},
        {4, 6, 5, 7},
        {4, 17, 5, 18},
        {4, 30, 5, 31},
        {4, 34, 5, 36},
        {4, 49, 5, 50},
        {5, 14, 6, 15},
        {5, 18, 6, 20},
        {5, 19, 7, 20},
        {5, 29, 6, 30},
        {5, 40, 6, 41},
        {5, 42, 6, 44},
        {5, 47, 7, 48},
        {6, 5, 7, 6},
        {6, 7, 7, 9},
        {6, 8, 12, 9},
        {6, 17, 7, 18},
        {6, 21, 7, 22},
        {6, 24, 7, 25},
        {6, 26, 7, 27},
        {6, 37, 7, 38},
        {6, 45, 8, 46},
        {7, 2, 8, 3},
        {7, 36, 9, 37},
        {7, 44, 8, 46},
        {8, 5, 9, 6},
        {8, 13, 9, 14},
        {8, 21, 9, 22},
        {8, 25, 9, 26},
        {8, 33, 9, 34},
        {9, 4, 11, 5},
        {9, 12, 10, 13},
        {9, 16, 13, 17},
        {9, 23, 10, 24},
        {9, 28, 10, 29},
        {9, 46, 10, 47},
        {10, 3, 11, 5},
        {10, 14, 11, 15},
        {10, 16, 13, 18},
        {10, 31, 12, 32},
        {10, 37, 11, 38},
        {10, 39, 11, 40},
        {10, 45, 11, 46},
        {11, 0, 12, 2},
        {11, 10, 13, 11},
        {11, 12, 13, 13},
        {11, 21, 12, 22},
        {11, 31, 12, 33},
        {11, 34, 12, 35},
        {11, 38, 12, 39},
        {11, 40, 14, 41},
        {11, 42, 12, 43},
        {11, 46, 12, 47},
        {12, 4, 13, 5},
        {12, 26, 13, 27},
        {12, 30, 14, 31},
        {12, 44, 13, 45},
        {13, 15, 14, 16},
        {13, 19, 14, 20},
        {13, 32, 14, 33},
        {13, 43, 14, 44},
        {14, 2, 15, 3},
        {14, 23, 15, 25},
        {14, 29, 15, 30},
        {14, 33, 15, 34},
        {14, 41, 15, 42},
        {15, 0, 16, 1},
        {15, 7, 16, 8},
        {15, 10, 16, 11},
        {15, 15, 16, 17},
        {15, 15, 17, 16},
        {15, 21, 16, 22},
        {15, 40, 16, 41},
        {15, 42, 16, 43},
        {15, 44, 16, 46},
        {15, 49, 16, 50},
        {16, 2, 19, 3},
        {16, 4, 17, 5},
        {16, 6, 18, 7},
        {16, 17, 17, 18},
        {16, 19, 18, 20},
        {16, 35, 17, 36},
        {17, 0, 19, 1},
        {17, 11, 19, 12},
        {17, 13, 18, 14},
        {17, 28, 18, 29},
        {17, 32, 19, 33},
        {17, 38, 19, 39},
        {17, 42, 19, 43},
        {17, 44, 18, 45},
        {17, 46, 18, 48},
        {18, 5, 21, 6},
        {18, 8, 19, 10},
        {18, 8, 20, 9},
        {18, 24, 19, 25},
        {18, 26, 19, 28},
        {18, 27, 20, 28},
        {18, 35, 20, 36},
        {18, 40, 19, 41},
        {18, 42, 19, 44},
        {19, 10, 20, 11},
        {19, 16, 20, 17},
        {19, 19, 20, 20},
        {19, 30, 20, 32},
        {20, 1, 21, 2},
        {20, 7, 21, 8},
        {20, 12, 21, 13},
        {20, 22, 23, 23},
        {20, 25, 21, 26},
        {20, 39, 21, 40},
        {20, 41, 21, 42},
        {20, 43, 21, 44},
        {20, 45, 21, 46},
        {20, 49, 21, 50},
        {21, 0, 22, 1},
        {21, 9, 22, 10},
        {21, 13, 22, 15},
        {21, 19, 22, 21},
        {21, 29, 22, 30},
        {21, 33, 22, 36},
        {21, 37, 22, 38},
        {21, 46, 23, 47},
        {22, 3, 26, 4},
        {22, 8, 23, 9},
        {22, 38, 23, 41},
        {22, 38, 24, 39},
        {22, 40, 24, 41},
        {23, 3, 26, 5},
        {23, 4, 27, 5},
        {23, 15, 26, 16},
        {23, 25, 24, 26},
        {23, 27, 24, 28},
        {23, 29, 24, 30},
        {23, 33, 24, 34},
        {23, 37, 24, 39},
        {24, 1, 26, 2},
        {24, 8, 25, 9},
        {24, 17, 25, 18},
        {24, 22, 25, 23},
        {24, 45, 26, 46},
        {25, 11, 26, 12},
        {25, 15, 26, 17},
        {25, 35, 26, 36},
        {25, 38, 26, 39},
        {25, 40, 26, 41},
        {25, 43, 26, 44},
        {25, 48, 26, 49},
        {26, 24, 27, 25},
        {26, 29, 27, 30},
        {26, 32, 28, 34},
        {26, 46, 27, 47},
        {26, 49, 27, 50},
        {27, 6, 29, 7},
        {27, 18, 28, 21},
        {27, 18, 29, 19},
        {27, 22, 28, 23},
        {27, 30, 28, 31},
        {27, 38, 28, 40},
        {27, 39, 29, 40},
        {27, 45, 28, 46},
        {27, 48, 28, 49},
        {28, 1, 29, 2},
        {28, 8, 29, 10},
        {28, 9, 30, 10},
        {28, 12, 29, 13},
        {28, 17, 29, 19},
        {28, 27, 29, 28},
        {28, 29, 29, 30},
        {28, 42, 29, 44},
        {28, 49, 29, 50},
        {29, 2, 30, 5},
        {29, 3, 31, 4},
        {29, 11, 30, 12},
        {29, 21, 30, 22},
        {29, 24, 31, 25},
        {29, 31, 30, 33},
        {29, 37, 30, 38},
        {29, 41, 30, 42},
        {29, 47, 30, 48},
        {30, 0, 31, 1},
        {30, 6, 31, 7},
        {30, 13, 31, 16},
        {30, 17, 31, 18},
        {30, 42, 31, 43},
        {31, 1, 32, 3},
        {31, 12, 33, 13},
        {31, 16, 34, 17},
        {31, 20, 32, 21},
        {31, 23, 33, 24},
        {31, 27, 36, 28},
        {31, 29, 32, 30},
        {31, 37, 32, 38},
        {31, 41, 32, 42},
        {31, 48, 32, 49},
        {32, 4, 33, 5},
        {32, 30, 33, 31},
        {32, 35, 33, 36},
        {32, 44, 34, 45},
        {33, 2, 34, 4},
        {33, 25, 34, 26},
        {33, 39, 36, 40},
        {33, 47, 34, 48},
        {34, 1, 35, 2},
        {34, 5, 35, 6},
        {34, 10, 35, 11},
        {34, 26, 36, 28},
        {34, 32, 35, 33},
        {34, 37, 35, 38},
        {34, 39, 35, 41},
        {34, 42, 35, 43},
        {34, 49, 35, 50},
        {35, 0, 36, 1},
        {35, 2, 36, 3},
        {35, 11, 36, 12},
        {35, 19, 36, 20},
        {35, 23, 37, 24},
        {36, 1, 37, 2},
        {36, 3, 37, 5},
        {36, 14, 37, 15},
        {36, 16, 37, 17},
        {36, 20, 38, 21},
        {36, 25, 37, 26},
        {36, 29, 37, 30},
        {36, 35, 37, 36},
        {36, 38, 37, 39},
        {36, 42, 38, 43},
        {36, 45, 37, 47},
        {36, 46, 38, 47},
        {36, 48, 37, 49},
        {37, 7, 39, 8},
        {37, 9, 38, 10},
        {37, 12, 40, 13},
        {37, 22, 38, 23},
        {37, 24, 39, 25},
        {37, 31, 38, 32},
        {38, 0, 39, 1},
        {38, 6, 39, 8},
        {38, 16, 39, 18},
        {38, 17, 40, 18},
        {38, 24, 39, 26},
        {38, 28, 39, 29},
        {38, 39, 39, 40},
        {38, 44, 39, 45},
        {38, 49, 40, 50},
        {39, 20, 40, 21},
        {39, 26, 40, 27},
        {39, 30, 40, 32},
        {39, 30, 41, 31},
        {39, 37, 40, 38},
        {39, 42, 40, 44},
        {39, 43, 41, 44},
        {39, 47, 40, 48},
        {40, 3, 41, 4},
        {40, 15, 42, 16},
        {40, 22, 41, 24},
        {40, 23, 42, 24},
        {40, 29, 41, 31},
        {40, 43, 41, 46},
        {40, 44, 42, 46},
        {40, 48, 41, 49},
        {41, 0, 42, 1},
        {41, 11, 42, 12},
        {41, 13, 42, 14},
        {41, 15, 42, 17},
        {41, 16, 43, 17},
        {41, 27, 42, 29},
        {41, 37, 42, 38},
        {41, 41, 42, 42},
        {41, 44, 42, 48},
        {41, 46, 43, 47},
        {42, 8, 43, 9},
        {42, 39, 43, 40},
        {42, 42, 43, 43},
        {42, 48, 43, 50},
        {43, 1, 44, 3},
        {43, 9, 44, 10},
        {43, 17, 44, 19},
        {43, 28, 45, 29},
        {43, 34, 44, 35},
        {43, 38, 44, 39},
        {43, 45, 44, 46},
        {44, 0, 45, 1},
        {44, 3, 45, 4},
        {44, 22, 45, 23},
        {44, 30, 45, 33},
        {44, 30, 47, 31},
        {44, 32, 46, 33},
        {44, 44, 46, 45},
        {44, 48, 46, 49},
        {45, 12, 46, 13},
        {45, 19, 46, 20},
        {45, 29, 46, 31},
        {46, 14, 47, 15},
        {46, 21, 48, 22},
        {46, 24, 47, 25},
        {46, 34, 47, 35},
        {46, 41, 47, 42},
        {47, 2, 48, 3},
        {47, 4, 48, 5},
        {47, 6, 48, 7},
        {47, 18, 48, 19},
        {47, 27, 49, 28},
        {47, 33, 49, 34},
        {47, 44, 50, 45},
        {48, 0, 49, 1},
        {48, 3, 49, 4},
        {48, 7, 49, 8},
        {48, 22, 49, 23},
        {48, 33, 49, 35},
        {48, 39, 49, 40},
        {48, 44, 49, 46},
        {49, 5, 50, 6},
        {49, 11, 50, 13},
        {49, 14, 50, 15},
        {49, 18, 50, 19},
        {49, 25, 50, 26},
        {49, 35, 50, 38},
        {49, 40, 50, 41},
        {49, 48, 50, 49}
    };

    int expected_sols = sizeof(expected_mers) / sizeof(MaximumEmptyRectangle);

    REQUIRE(rects.size() == expected_sols);
    for (int i = 0; i < expected_sols; i++) {
        REQUIRE( contains_rectangle(rects, expected_mers[i]) );
    }
}

TEST_CASE( "find_all_maximum_empty_rectangles: example 4 works ") {
    // 0011000000000010000101000010010000000100
    // 1110110000001000001000000010011001000000
    // 1000100000010000100000011000001011000110
    // 1000000000111000010100000010011001000011
    // 0001000000001100000010010001000001000000
    // 0000101000000010000000101000000100000001
    // 1010000000001000010000011000010000010010
    // 1000000001010001000000100010000000000000
    // 0100100000000000000010000001000100100110
    // 1100000101000001110001000001100000100000
    // 0100000010101001010010001000001000000000
    // 0000001100100001110000000100000000011000
    // 0000100101000001000001000000001000000001
    // 0001100000010000000000000000000000010100
    // 1000000001000010000000010010001100000110
    bool occupied[40][15] = {
        {1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0}
    };

    std::vector<MaximumEmptyRectangle> rects = find_all_maximum_empty_rectangles<40, 15>(occupied);

    MaximumEmptyRectangle expected_mers[169] = {
        {0, 1, 1, 5},
        {0, 1, 3, 4},
        {0, 2, 4, 4},
        {0, 3, 6, 4},
        {0, 6, 1, 7},
        {0, 9, 3, 11},
        {0, 9, 4, 10},
        {0, 14, 2, 15},
        {1, 0, 3, 4},
        {1, 0, 9, 1},
        {1, 7, 2, 13},
        {1, 7, 9, 8},
        {1, 9, 3, 13},
        {1, 11, 4, 13},
        {1, 11, 10, 12},
        {2, 0, 3, 8},
        {2, 2, 4, 8},
        {2, 3, 6, 6},
        {2, 4, 7, 6},
        {2, 4, 8, 5},
        {3, 2, 4, 10},
        {3, 7, 9, 9},
        {3, 8, 12, 9},
        {3, 11, 4, 14},
        {4, 10, 10, 12},
        {4, 10, 12, 11},
        {4, 14, 14, 15},
        {5, 0, 6, 13},
        {5, 0, 7, 3},
        {5, 0, 9, 2},
        {5, 1, 11, 2},
        {5, 4, 7, 9},
        {5, 6, 9, 9},
        {5, 6, 20, 7},
        {5, 10, 10, 13},
        {5, 12, 11, 13},
        {6, 10, 10, 15},
        {6, 12, 11, 15},
        {6, 13, 12, 15},
        {7, 6, 9, 15},
        {7, 8, 10, 15},
        {7, 8, 12, 11},
        {7, 9, 14, 10},
        {8, 0, 9, 4},
        {8, 3, 10, 4},
        {8, 5, 9, 15},
        {9, 3, 10, 5},
        {10, 0, 11, 3},
        {10, 0, 14, 1},
        {10, 2, 15, 3},
        {10, 5, 11, 11},
        {10, 5, 15, 7},
        {11, 2, 12, 7},
        {11, 2, 15, 4},
        {12, 0, 14, 4},
        {12, 1, 15, 4},
        {12, 1, 35, 2},
        {12, 5, 15, 8},
        {12, 12, 16, 13},
        {13, 0, 14, 10},
        {13, 1, 15, 9},
        {13, 8, 17, 9},
        {13, 11, 14, 15},
        {13, 11, 16, 14},
        {13, 11, 17, 12},
        {13, 13, 18, 14},
        {14, 10, 16, 14},
        {14, 10, 17, 12},
        {14, 10, 20, 11},
        {15, 0, 23, 2},
        {15, 8, 16, 15},
        {15, 8, 17, 12},
        {15, 9, 20, 11},
        {15, 9, 22, 10},
        {15, 13, 18, 15},
        {15, 14, 19, 15},
        {16, 0, 21, 3},
        {16, 4, 17, 5},
        {16, 6, 17, 12},
        {16, 6, 20, 8},
        {16, 7, 22, 8},
        {17, 12, 18, 15},
        {17, 12, 23, 13},
        {18, 0, 19, 13},
        {18, 0, 20, 11},
        {18, 0, 21, 4},
        {18, 3, 25, 4},
        {18, 5, 21, 6},
        {18, 7, 22, 10},
        {18, 8, 23, 9},
        {19, 12, 23, 14},
        {19, 13, 26, 14},
        {20, 11, 21, 15},
        {20, 11, 23, 14},
        {20, 11, 26, 12},
        {21, 3, 24, 5},
        {21, 6, 22, 14},
        {21, 6, 27, 7},
        {21, 10, 23, 14},
        {22, 0, 23, 7},
        {22, 1, 24, 7},
        {22, 1, 25, 4},
        {22, 1, 30, 3},
        {22, 5, 27, 7},
        {22, 10, 23, 15},
        {22, 13, 26, 15},
        {23, 1, 24, 8},
        {23, 5, 26, 8},
        {23, 9, 24, 10},
        {24, 0, 25, 4},
        {24, 0, 26, 3},
        {24, 10, 26, 12},
        {24, 10, 27, 11},
        {25, 4, 26, 15},
        {25, 4, 27, 7},
        {25, 4, 30, 5},
        {25, 8, 27, 11},
        {25, 8, 29, 10},
        {25, 9, 31, 10},
        {25, 12, 30, 13},
        {26, 1, 27, 7},
        {26, 1, 30, 5},
        {26, 3, 35, 4},
        {27, 0, 30, 5},
        {27, 7, 29, 10},
        {27, 7, 40, 8},
        {27, 11, 29, 15},
        {28, 6, 29, 15},
        {28, 6, 31, 8},
        {28, 9, 31, 11},
        {28, 10, 33, 11},
        {29, 0, 30, 8},
        {29, 5, 31, 8},
        {29, 5, 34, 6},
        {30, 5, 31, 11},
        {30, 7, 35, 9},
        {30, 14, 37, 15},
        {31, 1, 34, 6},
        {31, 1, 35, 5},
        {31, 2, 39, 3},
        {31, 4, 40, 5},
        {31, 10, 32, 15},
        {31, 10, 33, 12},
        {31, 13, 33, 15},
        {32, 0, 33, 12},
        {32, 0, 34, 10},
        {32, 0, 35, 5},
        {32, 0, 37, 1},
        {32, 7, 35, 10},
        {32, 9, 39, 10},
        {34, 7, 35, 15},
        {34, 9, 37, 15},
        {34, 9, 38, 12},
        {34, 9, 39, 11},
        {34, 10, 40, 11},
        {34, 13, 40, 14},
        {35, 4, 37, 8},
        {35, 4, 40, 6},
        {36, 0, 37, 3},
        {36, 4, 37, 15},
        {36, 7, 38, 12},
        {37, 2, 39, 6},
        {37, 3, 40, 6},
        {38, 1, 39, 6},
        {38, 1, 40, 2},
        {38, 13, 40, 15},
        {39, 0, 40, 2},
        {39, 3, 40, 9},
        {39, 12, 40, 15}
    };

    int expected_sols = sizeof(expected_mers) / sizeof(MaximumEmptyRectangle);

    REQUIRE(rects.size() == expected_sols);
    for (int i = 0; i < expected_sols; i++) {
        REQUIRE( contains_rectangle(rects, expected_mers[i]) );
    }
}
