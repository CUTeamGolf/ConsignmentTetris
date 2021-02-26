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

// //    /--- trouble case
// //   v
// // xxx--
// // xxxxx
// // xx--x
// // xxxxx
// // -xxxx
// bool occupied2[5][5] = {
//     {1, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0},
//     {0, 0, 1, 0, 0},
//     {0, 0, 1, 0, 1},
//     {0, 0, 0, 0, 1}
// };
//
// // ---X
// // --XX
// // -XXX
// // ---X
// bool occupied3[4][4] = {
//     {1, 1, 1, 1},
//     {1, 0, 1, 1},
//     {1, 0, 0, 1},
//     {0, 0, 0, 0}
// };
//
//
// // 00000000000000
// // 00110000000000
// // 00110000000000
// // 00110011111100
// // 00000011111100
// // 00000011111100
// // 00000011111100
// // 00000000000000
// // 00000000000000
// // 00000000000000
// bool occupied4[14][10] = {
//     {0,0,0,0,0,0,0,0,0,0},
//     {0,0,0,0,0,0,0,0,0,0},
//     {0,0,0,0,0,0,1,1,1,0},
//     {0,0,0,0,0,0,1,1,1,0},
//     {0,0,0,0,0,0,0,0,0,0},
//     {0,0,0,0,0,0,0,0,0,0},
//     {0,0,0,1,1,1,1,0,0,0},
//     {0,0,0,1,1,1,1,0,0,0},
//     {0,0,0,1,1,1,1,0,0,0},
//     {0,0,0,1,1,1,1,0,0,0},
//     {0,0,0,1,1,1,1,0,0,0},
//     {0,0,0,1,1,1,1,0,0,0},
//     {0,0,0,0,0,0,0,0,0,0},
//     {0,0,0,0,0,0,0,0,0,0}
// };

