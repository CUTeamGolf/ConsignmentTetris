#define GET_FULL_PROCESS_OPTIMISER_HEADER
#if __has_include("process_optimiser.h")
# include "process_optimiser.h"
#else
# include "../src/process_optimiser.h"
#endif

TEST_CASE( "empty box gives bottom-leftmost-corner position" ) {
    // the packing box
    double box_points[] = {-2, -2, -2, 5, 5, 5};

    // with no items
    double item_points[0];
    int item_points_size = 0;
    double item_indices[0];
    int item_indices_size = 0;
    
    // the item fits
    double dims[] = {6, 2, 4};

    double res[3];

    // ACTION
    bool can_fit = process_optimiser_main(box_points,
            item_points, item_points_size, item_indices,
            item_indices_size, dims, res);

    // ASSERT
    REQUIRE( can_fit );
    REQUIRE( res[0] == Approx(-2.0) );
    REQUIRE( res[1] == Approx(-2.0) );
    REQUIRE( res[2] == Approx(-2.0) );
}

TEST_CASE( "empty box and item barely fit 1" ) {
    // the packing box
    double box_points[] = {-3, -2, -1, 5, 7, 9};

    // with no items
    double item_points[0];
    int item_points_size = 0;
    double item_indices[0];
    int item_indices_size = 0;

    // the item fit
    double dims[] = {8, 9, 10};

    double res[3];

    // ACTION
    bool can_fit = process_optimiser_main(box_points,
            item_points, item_points_size, item_indices,
            item_indices_size, dims, res);

    // ASSERT
    REQUIRE( can_fit );
    REQUIRE( res[0] == Approx(-3.0) );
    REQUIRE( res[1] == Approx(-2.0) );
    REQUIRE( res[2] == Approx(-1.0) );
}

TEST_CASE( "empty box but item too big" ) {
    // the packing box
    double box_points[] = {-2, -2, -2, 5, 5, 5};

    // with no items
    double item_points[0];
    int item_points_size = 0;
    double item_indices[0];
    int item_indices_size = 0;

    // the item doesn't fit
    double dims[] = {6, 2, 7.001};

    double res[3];

    // ACTION
    bool stopped = false;
    try {
        bool can_fit = process_optimiser_main(box_points,
                item_points, item_points_size, item_indices,
                item_indices_size, dims, res);
    } catch (const char * c) {
        stopped = true;
    }
    REQUIRE( stopped );
}

TEST_CASE( "one item but no room because unstable" ) {
    // the packing box
    double box_points[] = {0, 0, 0, 5, 5, 5};

    // with no items
    double item_points[] = { 2.1, 2.3, 0.01, 2.3, 3.1, 1.56};
    int item_points_size = 6;
    double item_indices[] = {0};
    int item_indices_size = 1;

    // the item fits, but would be unstable
    double dims[] = {4.8, 4.8, 1};

    double res[3];

    // ACTION
    bool can_fit = process_optimiser_main(box_points,
            item_points, item_points_size, item_indices,
            item_indices_size, dims, res);

    // ASSERT
    REQUIRE( !can_fit );
}

TEST_CASE( "empty box and item barely fits 2") {
    // the packing box
    double box_points[] = {0, 0, 0, 5, 5, 5};

    // with no items
    double item_points[0];
    int item_points_size = 0;
    double item_indices[0];
    int item_indices_size = 0;

    // the item fits, but would be unstable
    double dims[] = {1, 5.0, 1};

    double res[3];

    // ACTION
    bool can_fit = process_optimiser_main(box_points,
            item_points, item_points_size, item_indices,
            item_indices_size, dims, res);

    // ASSERT
    REQUIRE( can_fit );
    REQUIRE( res[0] == Approx(0));
    REQUIRE( res[1] == Approx(0));
    REQUIRE( res[2] == Approx(0));
}

TEST_CASE( "no stable position" ) {
    // the packing box
    double box_points[] = {-1, -1, -1, 5, 5, 5};

    // with no items
    double item_points[] = {-0.9, 2.0, -1.0, 4.0, 3.0, 1.5,
                            0.0, 0.0, -1.0, 1.0, 1.0, 1.0};
    int item_points_size = 12;
    double item_indices[] = {0, 6};
    int item_indices_size = 2;

    // the item fits, but would be unstable
    double dims[] = {1.6, 3.5, 3.0};

    double res[3];

    // ACTION
    bool can_fit = process_optimiser_main(box_points,
            item_points, item_points_size, item_indices,
            item_indices_size, dims, res);

    // ASSERT
    REQUIRE( !can_fit );
}

TEST_CASE( "box is already full" ) {
    // the packing box
    double box_points[] = {-5, -5, -5, 5, 5, 5};

    // with no items
    double item_points[] = {-2.5, -2.3, -5, 3.1, 4.1, 3.0};
    int item_points_size = 6;
    double item_indices[] = {0};
    int item_indices_size = 1;

    // the item is too high to fit
    double dims[] = {3.1, 2.8, 2.1};

    double res[3];

    // ACTION
    bool can_fit = process_optimiser_main(box_points,
            item_points, item_points_size, item_indices,
            item_indices_size, dims, res);

    // ASSERT
    REQUIRE( !can_fit );
}
