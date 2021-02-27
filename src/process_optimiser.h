#ifndef PROCESS_OPTIMISER_HEADER
#define PROCESS_OPTIMISER_HEADER

/** TUNABLE PARAMETERS */
// the dimensions of the virtual co-ordinate system (accuracy-efficiency tradeoff)
#define MER_LENGTH_GRANULARITY 1000
#define MER_WIDTH_GRANULARITY  1000
#define MER_HEIGHT_GRANULARITY 1000
// XY area of the bounding box for the manipulator in the virtual co-ordinate system
#define ROBOT_ARM_LENGTH 50
#define ROBOT_ARM_WIDTH 50
// controls amount of debugging info (0 disables debugging)
#define DEBUG_VERBOSITY 0

// IGNORE THESE
#define STABILITY_LENGTH_GRANULARITY 100
#define STABILITY_WIDTH_GRANULARITY 100

/** debugging macros */
// basic print statements
#ifdef SS_STDIO_AVAILABLE
// debug print to simulink diagnostics window
# define dPrintf(verb, str, args) do { if (DEBUG_VERBOSITY >= verb) ssPrintf(str, args); } while (0)
#else
# define dPrintf(verb, str, ...) do { if (DEBUG_VERBOSITY >= (verb)) printf(str, ##__VA_ARGS__); } while (0)
#endif

// assertions
#ifdef SS_STDIO_AVAILABLE
# define dAssert(statement, msg) do { if (!(statement)) ssPrintf("ASSERTION FAILED: " msg "\n"); } while (0)
#else
# define dAssert(statement, msg) do { assert((statement) && (msg)); } while (0)
#endif

/** Matlab compiler workaround */
// The matlab-C++ linker only supports a subset
// of C++ and the standard library, so incompatible
// function prototypes are masked unless this flag
// is defined. Please define it before including this
// header file if you want to access those functions
// as well for e.g. unit testing.

//#define GET_FULL_PROCESS_OPTIMISER_HEADER

/** standard library features used in prototypes */
#include <vector>
#include <bitset>
#include <iostream>

/** Data containers (structs and classes) */
struct DUMMY_STRUCT_TO_SILENCE_ABOVE_COLORED_DOCUMENTATION {};

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
//     static auto get_heuristic_comp();

    /**
     * Checks if the MEC can fit some item in the virtual co-ordinate system
     * @param item_length
     * @param item_width
     * @param item_height
     * @return true if there is room for the item, false otherwise
     */
    bool can_fit_item(int item_length, int item_width, int item_height);

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

/* -------------------- phase 1 utility methods -------------------- */

#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
// TODO: docs
template <size_t array_length, size_t array_width>
void update_cache(int cache[array_width + 1], int x,
                  bool occupied_space[array_length][array_width]);
#endif

#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
// TODO: docs
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
 * @param occupied_space is the boolean matrix
 * @return a vector of MaximumEmptyRectangles that should
 * all satisy the above * described properties.
 */
template <size_t array_length, size_t array_width>
std::vector<MaximumEmptyRectangle> find_all_maximum_empty_rectangles(
        bool occupied_space[array_length][array_width]);
#endif

/* -------------------- phase 1 driver function -------------------- */

#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
std::vector<MaximumEmptyCuboid> find_all_maximum_empty_cuboids(
        std::vector<Cuboid> cuboids, int box_height);
#endif

/* -------------------- phase 2 utility methods -------------------- */
/**
 * manipulator_height is the z-value the manipulator needs to reach to place the item,
 *   so it's the sum of the empty space's z value and the item's height.
 */
#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
template <size_t array_length, size_t array_width>
void compute_reachable_positions(int item_length, int item_width, int manipulator_height,
                                 bool feasible_pos[array_length][array_width],
                                 const std::vector<MaximumEmptyCuboid>& empty_spaces);
#endif

/**
 * base_height is the height at which the base of the item will be placed i.e. the supporting ground height
 */
#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
template <size_t array_length, size_t array_width>
void compute_stable_positions(int item_length, int item_width, int base_height, bool stable_positions[array_length][array_width],
                              const std::vector<Cuboid> &cuboids);
#endif
/* -------------------- phase 2 driver function -------------------- */

/**
 * Given a list of candidates, picks a position from the best
 * one that works, where "works" is defined as:
 *   (i) the item fits in the EMC without clipping through it
 *   (ii) the item is stable (@see compute_stable_positions)
 *   (iii) the EMC extends all the way to the top of the packing box
 * and "best" is defined as:
 *   TODO: explain
 * @param length
 * @param width
 * @param height
 * @param candidates
 * @return TODO: usual case..
 *   When no solution is found, returns (-1, -1, -1)
 *   TODO: throw exception instead?
 */
#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
template <size_t array_length, size_t array_width>
std::tuple<int, int, int> pick_best_candidate(
        int length, int width, int height,
        std::vector<MaximumEmptyCuboid>& candidates,
        std::vector<Cuboid>& cuboids);
#endif


/* -------------------- main driver function -------------------- */

/**
 * TODO: docs
 * @param box_points
 * @param item_points
 * @param item_points_size
 * @param item_indices
 * @param item_indices_size
 * @param tetromino_position
 * @return
 */
bool process_optimiser_main(const double * box_points,
                            const double * item_points,
                            int item_points_size,
                            const double * item_indices,
                            int item_indices_size,
                            double * tetromino_dimensions,
                            double * tetromino_position);

/* ---------- Pseudo code for the algorithm as a whole ----------*/
/**
 * A high-level description of the algorithm to implement
 *
 * INPUT:
 *  - The position of the "deepest-bottom-leftmost" corner of the box
 *    (i.e. the corner with the lowest possible values for x,y,z) as
 *    well as its dimensions (length, width, height).
 *  - A list of length n with information about (a superset of)
 *    the items currently in the box. Let x_i, y_i, z_i be the
 *    position of the "deepest-bottom-leftmost" corner of the ith
 *    item and l_i, w_i, h_i be the corresponding dimensions.
 *  - Information about the item to be placed (l, w, h).
 *
 * PARAMETERS:
 *  - M (granularity for LER)
 *  - M' (granularity for stability check)
 *  - ERROR (deltaZ for determining if two items are at same height)
 *  - W_1 and W_2  weights for the two heuristics
 *
 * PSEUDOCODE:
 *
 * // Phase 1: get a list of Empty-Maximum-Space (EMS) candidates
 * sort the placed items by z + h (i.e. by height of the top face)
 * occupied_space <- M x M boolean matrix initialised to 0
 * candidates     <- empty list
 *
 * for i in n .. 0 do
 *   fill occupied_space with a 1 for each XY co-ordinate covered by the shadows of
 *       the [i .. n]th objects projected onto the XY plane
 *   if z_i + h_i is just slightly below previous height, skip this iteration
 *   MERs <- find_all_maximum_empty_rectangles(occupied_space)             // (*)
 *   foreach (ll, ur) in MERs do
 *     push ((ll.x, ll.y, z_i), (ur.x, ur.y, z_i + h_i)) to candidates
 *   end
 * end
 *
 * // Phase 2: filter and sort the candidates
 * P             <- empty list
 * foreach c in candidates do
 *   foreach allowed rotation of item i do
 *     if item i fits in EMS then
 *       push (c, rotation, most_stable_pos) to P
 *     endif
 *   end
 * end
 *
 * only keep the best candidates among those with same (ll, ur) (in XY space)
 *
 *
 * sort items in P in non-decreasing order by a score calculated as follows:
 *   W_1 * [(box_height - c.z) * 100 + (box_width - c.y) * 10 + (box_length - c.x)] + (?)
 *   W_2 * [XY area of c - XY area of item i]
 *
 * for  i in 0 .. length(P) do
 *   if item_is_stable(i, rotation) then use this solution with the
 *       corresponding stable position                                    // (**)
 * end
 *
 * if no stable solutions found
 *   say "next box"
 *
 * NOTES ON COMPLEMENTARY FUNCTIONS:
 *
 * (*) find_all_maximum_empty_rectangles:
 *   This function finds all rectangles covering only 0's
 *   This is possible to do in O(M^2) time, but
 *   the specific details are not here yet.
 *
 * (**) item_is_stable:
 *   make M' x M' boolean matrix of candidate rectangle
 *   foreach item packed directly under (to some error) do
 *     add 1's to the matrix where the item is located
 *   end
 *   for all possible lower left corners to place the item do
 *     find number of 1's in the area (can be done efficiently with pre-compute)
 *   end
 *   select the bottomost-leftmost corner such that stability (proportion of 1's)
 *       is within some margin of tolerance
 *   otherwise return false
 *
 *   Ideas: keep track of ur of placed items so no pre-processing
 *       where know it's all 0s
 *          let C[x, y] be the sum of 1's in M[0 .. x, 0 .. y], then
 *       can compute number of 1's in an area with
 *       C[x+w,y+l] - C[x+w, y] - C[x, y+l] + C[x, y]
 */

#endif //#ifndef PROCESS_OPTIMISER_HEADER
