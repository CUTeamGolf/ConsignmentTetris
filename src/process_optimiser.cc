#include "process_optimiser.h"

/**
 * A high-level description of the algorithm to implement
 *
 * INPUT:
 *  - The position of the "deepest-bottom-leftmost" corner of the box
 *    (i.e. the corner with the lowest possible values for x,y,z) as
 *    well as its dimensions (length, width, height).
 *  - A list of length n with information about a superset of
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

bool process_optimiser_main(const double * const box_position,
        const double * const box_dimensions, const int tetromino_id,
        const int tetrominos, double * tetromino_position,
        double * tetromino_rotation) {

    tetromino_position[0] = 10;
    tetromino_position[1] = 20;
    tetromino_position[2] = 30;

    tetromino_rotation[0] = 1;

    return true;
}
