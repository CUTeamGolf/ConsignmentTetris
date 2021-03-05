#ifndef PROCESS_OPTIMISER_HEADER
#define PROCESS_OPTIMISER_HEADER

/* --- TUNABLE PARAMETERS --- */
// the dimensions of the virtual co-ordinate system (accuracy-efficiency tradeoff)
#define MER_LENGTH_GRANULARITY 1000
#define MER_WIDTH_GRANULARITY  1000
#define MER_HEIGHT_GRANULARITY 1000
// XY area of the bounding box for the manipulator in the virtual co-ordinate system
#define ROBOT_ARM_LENGTH 30
#define ROBOT_ARM_WIDTH 30
// the fraction of ground support needed to deem a placement "stable"
#define STABILITY_SUPPORT_FRACTION 0.6
// controls amount of debugging info (0 disables debugging)
#define DEBUG_VERBOSITY 2

/* --- debugging macros --- */
// NOTE on SS_STDIO_AVAILABLE:
//   this macro is defined in <simstruc.h>,
//   so this should be included *before* process_optimiser.h

// basic print statements
#ifdef SS_STDIO_AVAILABLE
// debug print to simulink diagnostics window
# define dPrintf(verb, str, ...) do { if (DEBUG_VERBOSITY >= verb) ssPrintf(str, ##__VA_ARGS__); } while (0)
#else
# define dPrintf(verb, str, ...) do { if (DEBUG_VERBOSITY >= (verb)) printf(str, ##__VA_ARGS__); } while (0)
#endif

// assertions
#ifdef SS_STDIO_AVAILABLE
# define dAssertSoft(statement, msg, ...) do { if (!(statement)) { ssPrintf("ASSERTION FAILED: " msg "\n", ##__VA_ARGS__); ASSERTION_FAILURES++; } } while (0)
# define dAssertHard(statement, msg, ...) do { if (!(statement)) { ssPrintf("ASSERTION FAILED: " msg "\n", ##__VA_ARGS__); throw "STOPPING EXECUTION BECAUSE OF ASSERTION ERROR"; } } while (0)
#else
# define dAssertSoft(statement, msg, ...) do { if (!(statement)) { printf("ASSERTION FAILED: " msg "\n", ##__VA_ARGS__); ASSERTION_FAILURES++; } } while (0)
# define dAssertHard(statement, msg, ...) do { assert((statement) && (msg)); } while (0)
#endif

/* --- Matlab compiler workaround --- */
// The matlab-C++ linker only supports a subset
// of C++ and the standard library, so incompatible
// function prototypes are masked unless this flag
// is defined. Please define it before including this
// header file if you want to access those functions
// as well for e.g. unit testing. The flag is:
    #define GET_FULL_PROCESS_OPTIMISER_HEADER

/* --- standard library features used in prototypes --- */
#include <vector>
#include <bitset>
#include <iostream>

/**
 * Represents the free space in the
 * box to place the items in.
 *
 * The dimensions should not include the
 * thickness of the walls and the floor.
 *
 * @field x,y,z the MATLAB co-ordinates of the bottom-lower-left corner of the box
 * @field length,width,height the MATLAB dimensions of the box
 */
struct PackingBox {
    double x, y, z;
    double length, width, height;
};

/**
 * Represents an discretized bounding box around some object in
 * the virtual co-ordinate system.
 *
 * Both the x, y, and z co-ordinates are relative to the bottom-
 * -lower-left corner of the box. The top-upper-right corner
 * of the box has co-ordinates (MER_L_GRAN, MER_W_GRAN, MER_H_GRAN).
 *
 * @field x,y,z co-ordinates of the bottom-lower-left corner relative
 * to the packing box in the virtual co-ordinate system
 * @field length,width,height the dimensions of the cuboids
 *
 * @method compare less than
 */
struct Cuboid {
    int x, y, z;
    int length, width, height;

    /**
     * Custom comparison for sorting cuboids by z+height
     *
     * @param other the cube to sort against
     * @return true if this cube has a top-face lower than the other cube.
     */
    bool operator<(const Cuboid& other) const;
};

#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
/**
 * Auxiliary function for the BoxTetromino constructor.
 *
 * Computes the coordinate and size in some
 * virtual 1D coordinate system of size 0 <= x < GRANULARITY
 * based on a real co-ordinate and real size relative to another real co-ordinate
 * and real size.
 *
  * @param GRANULARITY the number of units in the resulting coordinate system
  * @param real_c real actual coordinate of point
  * @param real_size real actual length of line
  * @param packing_box_c real actual coordinate of origin
  * @param packing_box_size real actual size in which it's assumed real_size + real_c is less than
  * @return a pair of integer coordinate x and size s as described above.
  */
std::pair<int, int> box_tetromino_constructor_aux(double GRANULARITY, double real_c,
                                                  double real_size, double packing_box_c, double packing_box_size);
#endif

/**
 * Represents a simscape multibody box.
 *
 * @explanation
 * The x,y,z co-ordinates are those used in Simscape.
 * This includes the dimensions. When constructing
 * this object, this information, combined with
 * information about the box, is used to calculate
 * the co-orinates and dimensions in the virtual
 * co-ordinate system described above.
 *
 */
struct BoxTetromino : public Cuboid {
    double real_x, real_y, real_z;
    double real_length, real_width, real_height;

    /**
     * Initialised the fields and creates a discritised bounding box
     * in the virtual co-ordinate system. The following criteria
     * should be satisifed:
     * @criteria x less than real_x - pb.x
     * @criteria real_x + real_length - pb.x less than x + length
     *
     * @param x,y,z the matlab co-ordinates of the bottom-lower-left corner
     * of the box.
     * @param l,w,h the matlab dimensions of the box
     * @param pb a  PackingBox struct
     */
    BoxTetromino(double x, double y, double z,
                 double l, double w, double h,
                 const PackingBox & pb);
};

/**
 * Represents a rectangle of 0s that can't be expanded
 * any further in a boolean matrix.
 *
 * @field llx,lly the XY-coordinates of the lower-left corner
 * of the rectangle (inclusive)
 * @field urx,ury the XY-coordinates of the upper-right corner
 * of the rectangle (exclusive)
 *
 * @see find_all_maximum_empty_rectangles
 *
 */
struct MaximumEmptyRectangle {
    // lower left corner
    int llx, lly;
    // upper right corner (exclusive)
    int urx, ury;
};

/**
 * Represents a Maximum Empty Cuboid (MEC) i.e. a cuboid in the virtual co-ordinate
 * system that cannot be expanded by 1 in any of the 6 directions without
 * intersecting with some other object in the scene.
 *
 * @field x,y,z the co-ordinates of the bottom-lower-left corner of the MEC
 * @field length size in x-direction
 * @field width size in y-direction
 * @field height size in z=direction
 */
struct MaximumEmptyCuboid {
    int x, y, z;
    int length, width, height;

    /**
     *
     * @param mer A MaximumEmptyRectangle struct from which to get length, width, x, and y
     * @param z the height of the lower-face
     * @param height the height
     */
    MaximumEmptyCuboid(const MaximumEmptyRectangle &mer, int z, int height);

    /**
     * Custom compare for bottom face height of the MEC
     * @return a lambda that can be used to sort a list of MECs by their
     * z-value in non-decreasing order
     */
     // this is commented out due to the MEX compiler not supporting this
     // C++11? feature
//    static auto get_bottom_face_comp();

    /**
     * Custom comparison based on heuristics to decide which
     * of two candidates is better.
     *
     * A candidate is better if:
     * - it has a lower z co-ordinate
     * - none of the above, but it has a lower y co-ordinate
     * - none of the above, but it has a lower x co-ordinate
     * - none of the above but the volume is smaller
     * @return a lambda that can be used to sort a list of MECs by the above criteria
     */
     // this is commented out due to the MEX compiler not supporting this
     // C++11? feature
//     static auto get_heuristic_comp();

    /**
     * Checks if the MEC can fit some item in the virtual co-ordinate system
     * @param item_length
     * @param item_width
     * @param item_height
     * @return true if there is room for the item, false otherwise
     */
    bool can_fit_item(int item_length, int item_width, int item_height) const;

#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
    //// Used for exporting a string representation of the MEC that the cuboid_visualiser.m script supports
    friend std::ostream& operator<<(std::ostream& os, const MaximumEmptyCuboid& mec);
#endif
};

/* -------------------- General utility methods -------------------- */

#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
/**
 * Fills the boolean matrix with 1s in the XY area of the Cuboid passed.
 *
 * @details
 * After calling this function, the boolean matrix occupied_space should be
 * true at locations [c.x:c.x+l, c.y:c.y+w] where the ends are exclusive.
 *
 * @tparam array_length the length of the array passed
 * @tparam array_width the width of the array passed
 * @param occupied_space a boolean matrix
 * @param c a Cuboid in a virtual co-ordinate system of the same size as the template parameters
 */
template<size_t array_length, size_t array_width>
void fill_occupied_space(bool occupied_space[array_length][array_width], const Cuboid & c);
#endif

#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
/**
 * Prints a 2D boolean array to stdout in a readable format
 * @tparam array_length the length of the array
 * @tparam array_width the width of the passed array
 * @param verbosity if this parameter is higher than DEBUG_VERBOSITY,
 *   nothing will be printed to stdout.
 * @param arr the passed boolean array
 */
template <size_t array_length, size_t array_width>
void dPrint_array(int verbosity, bool arr[array_length][array_width]);
#endif

/* -------------------- phase 1 utility methods -------------------- */

#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
/**
 * Utility method only used by find_all_maximum_empty_rectangles.
 * If given a valid cache for x + 1, the method updated the cache
 * to be valid for x. A cache is valid for x if:
 *   x' = cache[y] denotes that all entries in
 *   occupied_space[x .. x'][y] starting from (x, y) and ending
 *   at (x', y) (inclusive) are consecutive 0s.
 * @tparam array_length length of array
 * @tparam array_width one less than width of array
 * @param cache a valid cache for x + 1
 * @param x a x coordinate
 * @param occupied_space a boolean matrix
 */
template <size_t array_length, size_t array_width>
void update_cache(int cache[array_width + 1], int x,
                  bool occupied_space[array_length][array_width]);
#endif

#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
/**
 * Removes all rectangles that are fully surrounded by another rectangle
 * on all four sides.
 *
 * @Precondition
 * For all rectangles in the input, if it is not a maximum empty rectangle,
 * it should only be possible to extend it 1 or more units in
 * the -x direction to get a valid maximum empty rectangle. No other expansion
 * directions should be possible.
 *
 * @Postcondition
 * Every rectangle in the result is a valid maximum empty rectangle.
 *
 * @param rectangles a vector of MaximumEmptyRectangles that satisfies
 * the pre-condition described above.
 * @return a vector of MaximumEmptyRectangles that satisfies the post-condition
 * described above.
 */
std::vector<MaximumEmptyRectangle> remove_inner_rectangles(
        std::vector<MaximumEmptyRectangle> & rectangles);
#endif

#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
/**
 * Finds all the MERs of 0s in the passed boolean matrix, having the
 * following properties.
 *
 * @coordinate_system This method assumes a co-ordinate system where
 * x,y ranges from 0,0 to array_length-1,array_width-1 (inclusive),
 * respectively, and the entry at that coordiante is specified
 * by occupied_space[x][y].
 *
 * @MaximumEmptyRectangle_properties the booleans at indices
 * mer.llx &lt;= x &lt; mer.urx and mer.lly &lt;= y &lt; mer.ury
 * should be false.
 * @MaximumEmptyRectangle_properties extending the rectangle in
 * any of the four directions should introduce at least one entry
 * with a true in it, or cause the rectangle to go out of bounds.
 *
 * @tparam array_length the size of the first dimension of the array
 * @tparam array_width the size of the second dimension of the array
 * @param occupied_space is the boolean matrix
 * @return a vector of MaximumEmptyRectangles that should
 * all satisfy the above described properties.
 */
template <size_t array_length, size_t array_width>
std::vector<MaximumEmptyRectangle> find_all_maximum_empty_rectangles(
        bool occupied_space[array_length][array_width]);
#endif

/* -------------------- phase 1 driver function -------------------- */

#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
/**
 * Takes information about the box and its contents and finds all
 * maximum empty cuboids (MEC) composed of empty space.
 *
 * @MaximumEmptyCuboid_properties There is no cuboid c in the
 * input list cuboids such that it intersects with the MEC
 * @MaximumEmptyCuboid_properties Expanding the MEC in any of
 * the 6 possible direction by 1 unit should either make it
 * intersect with a cuboid from the input list, or cause the MEC
 * to go out of bounds in the coordinate system where 0 <= x < array_length,
 * 0 <= y < array_width, 0 <= z < box_height
 *
 * @tparam array_length number of units in the x-direction in the coordinate system
 * @tparam array_width number of units in the y-direction in the coordinate system
 * @param cuboids a vector of cuboids where each cuboid should be in bound
 * in the above described coordinate system
 * @param box_height number of units in the z-direction in the coordinate system
 * @return a vector of MECs satisfying the properties described above.
 */
template <size_t array_length, size_t array_width>
std::vector<MaximumEmptyCuboid> find_all_maximum_empty_cuboids(
        std::vector<Cuboid> cuboids, int box_height);
#endif

/* -------------------- phase 2 utility methods -------------------- */
#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
/**
 * Fills the feasible_pos array at entry (x, y) with a 1 if there
 * is some MEC in empty_spaces with a z-value lower than manipulator_height
 * that can fit an item of dimensions item_length x item_width were it to
 * be placed with its left corner at (x, y). In other words, if feasible_pos[x][y]
 * is true, the manipulator arm has room to place an item at bottom lower left corner
 * (x, y, manipulator_height - item_height).
 *
 * The empty_spaces vector should include a dummy MEC with z = -1 that
 * represents the empty space of the area of the box.
 *
 * @tparam array_length size of x dimension
 * @tparam array_width size of y dimension
 * @param item_length
 * @param item_width
 * @param manipulator_height the height at which the manipulator will drop the item
 * @param feasible_pos
 * @param empty_spaces a vector of MECs
 */
template <size_t array_length, size_t array_width>
void compute_reachable_positions(int item_length, int item_width, int manipulator_height,
                                 bool feasible_pos[array_length][array_width],
                                 const std::vector<MaximumEmptyCuboid>& empty_spaces);
#endif

#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
/**
 * Fills the stable_positions array at entry (x, y) with a 1 if
 * placing the lower left corner of an item with
 * dimensions item_length x item_width there
 * would result in STABILITY_SUPPORT_FRACTION of the item's base
 * being supported by cuboids in cuboids.
 *
 * @tparam array_length size of first dimensions of stable_position
 * @tparam array_width size of second dimension of stable_position
 * @param item_length length of item to make stable
 * @param item_width width of item to make stable
 * @param base_height z-value to place item at. This value <strong>must be equal
 * to c.z + c.height for some c in cuboids</strong>, otherwise the method will
 * halt.
 * @param stable_positions boolean 2D array that will have its values
 * overwritten
 * @param cuboids a vector of the cuboids currently in the box. These
 * must be sorted in non-decreasing order by z + height.
 */
template <size_t array_length, size_t array_width>
void compute_stable_positions(int item_length, int item_width, int base_height,
                              bool stable_positions[array_length][array_width],
                              const std::vector<Cuboid> &cuboids);
#endif
/* -------------------- phase 2 driver function -------------------- */

#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
/**
 * Given a list of candidate MECs, picks a bottom lower left position
 * to place an item of dimensions length x width x height that is
 * (i) possible and (ii) the best according to our heuristic comparing
 * possible positions.
 *
 * @possible the item fits in the EMC without clipping through it
 * @possible the item is stable (see compute_stable_positions)
 * @possible the EMC extends all the way to the top of the packing box
 *
 * @heuristic a lower z value is always better
 * @heuristic if z value is the same, a lower y value is better
 * @heuristic if z and y is the same, a lower x is better
 *
  * @tparam array_length size of the first dimension of the
  * coordinate system used by the cuboids and candidates
  * @tparam array_width size of the second dimension of the
  * coordinate system used by the cuboids and candidates
  * @param length length of cuboid to place
  * @param width width of cuboid to place
  * @param height height of cuboid to place
  * @param candidates a list of candidate MECs computed based
  * on the cuboid already in the box. This vector will be modified
  * to be sorted according to a heurisitic.
  * @param cuboids a list of cuboids already in the box. This vector
  * will be modified to be sorted by ascending z + height
  * @return a tuple (x, y, z) at which to place the bottom lower left
  * corner of the item. If no possible positions are found (see above),
  * the tuple (-1, -1, -1) is returned.
 */
template <size_t array_length, size_t array_width>
std::tuple<int, int, int> pick_best_candidate(
        int length, int width, int height,
        std::vector<MaximumEmptyCuboid>& candidates,
        std::vector<Cuboid>& cuboids);
#endif


/* -------------------- main driver function -------------------- */

/**
 * Takes information of the packing box and its contents, and tries to find
 * a position in which an item of dimensions specified in item_points can fit.
 * It then puts the result in result_position.
 *
 * @headerfile_parameters MER_LENGTH_GRANULARITY specifies the size of the first
 * dimension of the virtual coordinate system.
 * @headerfile_parameters MER_WIDTH_GRANULARITY specifies the size of the second
 * dimension of the virtual coordinate system.
 * @headerfile_parameters MER_HEIGHT_GRANULARITY specifies the size of the third
 * dimension of the virtual coordinate system.
 *
 * @param box_points an array of length 6 where the first three elements (x, y, z)
 * specifies the position of the inner bottom leftmost lower corner of the packing
 * box in real matlab coordinates.
 * @param item_points an array of length item_points_size where each tuple (x, y, z)
 * specifies a point belonging to an item (see item_indices)
 * @param item_points_size size of item_points, should be a multiple of 3
 * @param item_indices each item x in this list specifies that tuples in
 * item_points[x ... y) belong to one cuboid, where y is the next value in item_indices,
 * and is the end of the list of x is the last item
 * @param item_indices_size the number of cuboids i.e. size of item_points
 * @param tetromino_dimensions an array of size 3 specifying the dimensions of the item to pack,
 * length, width, height
 * @param result_position the resulting position (x, y, z) is saved in this array, so it must be
 * passed by reference
 * @return true if an possible position was found. False otherwise, in which case the values
 * in result_position will be meaningless.
 */
bool process_optimiser_main(const double * box_points,
                            const double * item_points,
                            int item_points_size,
                            const double * item_indices,
                            int item_indices_size,
                            double * tetromino_dimensions,
                            double * result_position);

#endif //#ifndef PROCESS_OPTIMISER_HEADER
