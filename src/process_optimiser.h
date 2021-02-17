#ifndef PROCESS_OPTIMISER_HEADER
#define PROCESS_OPTIMISER_HEADER

#include <vector>
#include <bitset>
#include <iostream>

#define MER_LENGTH_GRANULARITY 1000
#define MER_WIDTH_GRANULARITY  1000
#define MER_HEIGHT_GRANULARITY 1000
#define STABILITY_LENGTH_GRANULARITY 100
#define STABILITY_WIDTH_GRANULARITY 100

//#define ENABLE_DEBUG
#ifdef ENABLE_DEBUG
    #define debug(msg) {std::cout << msg << std::endl;};
#else
    #define debug(msg) {};
#endif

/**** #define GET_FULL_PROCESS_OPTIMISER_HEADER ****/
// The matlab-C++ linker only supports a subset
// of C++ and the standard library, so incompatible
// function prototypes are masked unless this flag
// is defined. Please define it before including this
// header file if you want to access those functions
// as well for e.g. unit testing.
// TODO: figure out if the matlab compiler has any
//    specific flags we can #ifndef on instead

/**
 * Represents the free space in the
 * box to place the items in.
 *
 * The dimensions should not include the
 * thickness of the walls and the floor.
 */
struct PackingBox {
    double x, y, z;
    double length, width, height;
};

/**
 * Represents an discretized bounding box around some object in
 * a virtual co-ordinate system.
 *
 * Both the x, y, and z co-ordinates are relative to the bottom-
 * -lower-left corner of the box. The top-upper-right corner
 * of the box has co-ordinates (MER_L_GRAN, MER_W_GRAN, MER_H_GRAN).
 */
struct Cuboid {
    int x, y, z;
    int length, width, height;
};

/**
 * Represents a simscape multibody box.
 *
 * The x,y,z co-ordinates are those used in Simscape.
 * This includes the dimensions. When constructing
 * this object, this information, combined with
 * information about the box, is used to calculate
 * the co-orinates and dimensions in the virtual
 * co-ordinate system described above.
 */
struct BoxTetromino : public Cuboid {
    double real_x, real_y, real_z;
    double real_length, real_width, real_height;

    BoxTetromino(double x, double y, double z,
                 double l, double w, double h,
                 const PackingBox & pb);
};

/**
 * Represents a rectangle of 0s that can't be expanded
 * any further in a boolean matrix.
 *
 * The boolean matrix has dimensions
 *   MER_LENGTH_GRANULARITY x MER_WIDTH_GRANULARITY
 * This POD is mainly used by @code find_all_maximum_rectangles
 */
struct MaximumEmptyRectangle {
    int x, y;
    int length, width;
};

/**
 * Represents a MEC. TODO: docs
 *
 * TODO: fields
 * @field stable_position contains the xy co-ordinates of the lower-left
 *      corner of the rectangle at the floor of the MEC where the last
 *      item to be passed to @method can_fit_item was found to fit.
 */
class MaximumEmptyCuboid {
    int x, y, z;
    int length, width, height;

    bool has_computed_stable_position;
    std::pair<int, int> stable_position;

public:
    // construct from MER object
    MaximumEmptyCuboid(const MaximumEmptyRectangle &mer, int z, int height);

    /**
     * Checks if this MEC has a stable position for an item with XY
     * dimensions @param item_length and @param item_width. If so,
     * the @field stable_position is updated and
     * @method get_stable_position can be called to
     * fetch this information.
     *
     * TODO: elaborate on threshold and stuff
     *
     * @param candidates -- TODO: explain
     * @return whether the item has a stable position in this MEC or not.
     */
    bool has_stable_position(int item_length, int item_width, double z,
                             const std::vector<MaximumEmptyCuboid> & candidates);

    /**
     * TODO: explain
     * @return
     */
    std::tuple<int, int, int> get_stable_position();

    // TODO: docs
    bool can_fit_item(int item_length, int item_width, double item_height);

    // TODO: docs, for sorting the candidates based on heuristic
    //    described in pseudo-code
    bool operator < (const MaximumEmptyCuboid & other) const;
};

/**
 * Fills the boolean matrix with 1s at locations [c.x:c.x+l, c.y:c.y+w]
 * i.e. at the "shadows" of the item.
 *
 * @tparam array_length
 * @tparam array_width
 * @param occupied_space -- the boolean matrix
 * @param c
 */
#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
template<size_t array_length, size_t array_width>
void fill_occupied_space(bool occupied_space[array_length][array_width],
                         const Cuboid & c);
#endif

/**
 * Finds all the MERs of 0s in the passed boolean matrix. All these
 * rectangles should have the properties
 *  (i) all bools inside them are false
 *  (ii) no row above or column to the side should contain all 0s
 *
 *  Matlab does not allow returning custom types, so the result
 *  is stored in the result parameter passed as a reference.
 *
 * @param occupied_space -- a boolean matrix
 * @return
 */
#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
std::vector<MaximumEmptyRectangle> find_all_maximum_empty_rectangles(
        bool occupied_space[MER_LENGTH_GRANULARITY][MER_WIDTH_GRANULARITY]);
#endif

/**
 * Finds all the MECs in the box based on the cuboids already there.
 *
 * TODO: elaborate
 *
 * @param cuboids
 * @return
 */

#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
std::vector<MaximumEmptyCuboid> find_all_maximum_empty_cuboids(
        std::vector<Cuboid> cuboids, const PackingBox & pb);
#endif

/**
 * Given a list of candidates, picks a position from the best
 * one that works, where "works" is defined as:
 *   (i) the item fits in the EMC without clipping through it
 *   (ii) the item is stable (@see has_stable_position)
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
std::tuple<double, double, double> pick_best_candidate(
        int length, int width, int height,
        std::vector<MaximumEmptyCuboid> candidates);
#endif

// TODO: add process_optimiser_main when it makes more sense
bool process_optimiser_main(const double * const box_pos,
                            const double * const box_dim,
                            double * res);

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

#endif