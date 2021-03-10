#define GET_FULL_PROCESS_OPTIMISER_HEADER
#if __has_include("process_optimiser.h")
# include "process_optimiser.h"
#else
# include "../src/process_optimiser.h"
#endif

TEST_CASE( " discritized cuboid doesn't intersect packing box ") {
    PackingBox test_pb = {0, 0, 0, 1, 1, 1};

    BoxTetromino bt = {0.00001, 0.00001, 0.00001, 0.99998, 0.99998, 0.99998, test_pb};
    REQUIRE( bt.x == 0 );
    REQUIRE( bt.y == 0 );
    REQUIRE( bt.z == 0 );
    REQUIRE( bt.length == MER_LENGTH_GRANULARITY);
    REQUIRE( bt.width  == MER_WIDTH_GRANULARITY );
    REQUIRE( bt.height == MER_HEIGHT_GRANULARITY);
}
