#include <iostream>
#include <algorithm>
#include <tuple>
#include <stack>
#include <cmath>
#include <utility>
#include <string>
#if __has_include(<simstruc.h>)
# include <simstruc.h>
#endif
#include <cassert>

#include "process_optimiser.h"

// for counting the number of soft assertions
int ASSERTION_FAILURES = 0;

/*  ---------------------- CLASS METHODS ------------------------------------ */

bool Cuboid::operator<(const Cuboid &other) const {
    return this->z + this->height < other.z + other.height;
}

// TODO: docs
std::pair<int, int> box_tetromino_constructor_aux(double GRANULARITY, double real_c,
                                   double real_size, double packing_box_c, double packing_box_size) {
    // position of lower left corner
    int lower_cord = floor(GRANULARITY * (real_c - packing_box_c) / packing_box_size);
    int upper_cord = ceil(GRANULARITY * (real_c + real_size - packing_box_c) / packing_box_size);
    // the size along the dimension is simple to compute (or -1?)
    return {lower_cord, upper_cord - lower_cord};

}
// TODO: docs
BoxTetromino::BoxTetromino(double x, double y, double z,
                           double l, double w, double h, const PackingBox & pb) : Cuboid(),
        real_x(x), real_y(y), real_z(z), real_length(l), real_width(w), real_height(h) {
    // compute the dimensions by bounding the real values
    std::pair<int, int> xDim = box_tetromino_constructor_aux(MER_LENGTH_GRANULARITY,
                                                             this->real_x, this->real_length, pb.x, pb.length);
    std::pair<int, int> yDim = box_tetromino_constructor_aux(MER_WIDTH_GRANULARITY,
                                                             this->real_y, this->real_width, pb.y, pb.width);
    std::pair<int, int> zDim = box_tetromino_constructor_aux(MER_HEIGHT_GRANULARITY,
                                                             this->real_z, this->real_height, pb.z, pb.height);
    // These values should now be integers between 0 and MER_LENGTH_GRANULARITY
    this->x = xDim.first;
    this->length = xDim.second;
    this->y = yDim.first;
    this->width = yDim.second;
    this->z = zDim.first;
    this->height = zDim.second;

    // Do assertions on the results
    dAssertSoft(this->x >= 0 && this->x < MER_LENGTH_GRANULARITY, "Constructing BoxTetromino cuboid: computed x value is within bounds: 0 <= %d < %d", this->x, MER_LENGTH_GRANULARITY);
    dAssertSoft(this->y >= 0 && this->y < MER_WIDTH_GRANULARITY, "Constructing BoxTetromino cuboid: computed y value is within bounds: 0 <= %d < %d", this->y, MER_WIDTH_GRANULARITY);
    dAssertSoft(this->z >= 0 && this->z < MER_HEIGHT_GRANULARITY, "Constructing BoxTetromino cuboid: computed z value is within bounds: 0 <= %d < %d", this->z, MER_HEIGHT_GRANULARITY);
    dAssertSoft(this->x + this->length < MER_LENGTH_GRANULARITY, "Constructing BoxTetromino cuboid: computed length in x-dimension is within bounds: x (%d) + l (%d) = %d < %d", this->x, this->length, this->x + this->length, MER_LENGTH_GRANULARITY);
    dAssertSoft(this->length > 0, "Constructing BoxTetromino cuboid: the cuboid has a zero or lower length: %d", this->length);
    dAssertSoft(this->y + this->width < MER_WIDTH_GRANULARITY, "Constructing BoxTetromino cuboid: computed length in y-dimension is within bounds: y (%d) + w (%d) = %d < %d", this->y, this->width, this->y + this->width, MER_WIDTH_GRANULARITY);
    dAssertSoft(this->width > 0, "Constructing BoxTetromino cuboid: the cuboid has a zero or lower width: %d", this->width);
    dAssertSoft(this->z + this->height < MER_HEIGHT_GRANULARITY, "Constructing BoxTetromino cuboid: computed length in z-dimension is within bounds: z (%d) + h (%d) = %d < %d", this->z, this->height, this->z + this->height, MER_HEIGHT_GRANULARITY);
    dAssertSoft(this->height > 0, "Constructing BoxTetromino cuboid: the cuboid has a zero or lower height: %d", this->height);

}

MaximumEmptyCuboid::MaximumEmptyCuboid(
        const MaximumEmptyRectangle & mer, int z, int height) {
    this->x = mer.llx;
    this->y = mer.lly;
    this->z = z;

    this->length = mer.urx - mer.llx;
    this->width  = mer.ury - mer.lly;
    this->height = height;
}

#define BOTTOM_FACE_COMP ([](const MaximumEmptyCuboid &cube1, const MaximumEmptyCuboid &cube2) { return cube1.z < cube2.z; })
//auto MaximumEmptyCuboid::get_bottom_face_comp() {
//    return [](const MaximumEmptyCuboid &cube1, const MaximumEmptyCuboid &cube2) {
//        return cube1.z < cube2.z;
//    };
//}

#define HEURISTIC_COMP ([](const MaximumEmptyCuboid& cube1, const MaximumEmptyCuboid& cube2) { if (std::tie(cube1.z, cube1.y, cube1.x) == std::tie(cube2.z, cube2.y, cube2.x)) { return (cube1.z * cube1.y * cube1.x) < (cube2.z * cube2.y * cube2.x); } else { return std::tie(cube1.z, cube1.y, cube1.x) < std::tie(cube2.z, cube2.y, cube2.x); } })
//auto MaximumEmptyCuboid::get_heuristic_comp() {
//    return [](const MaximumEmptyCuboid& cube1, const MaximumEmptyCuboid& cube2) {
//        // we sort by volume in this case
//        if (std::tie(cube1.z, cube1.y, cube1.x) == std::tie(cube2.z, cube2.y, cube2.x)) {
//            return (cube1.z * cube1.y * cube1.x) < (cube2.z * cube2.y * cube2.x);
//        } else {
//            return std::tie(cube1.z, cube1.y, cube1.x) < std::tie(cube2.z, cube2.y, cube2.x);
//        }
//    };
//}

bool MaximumEmptyCuboid::can_fit_item(int item_length, int item_width, int item_height) {
    return this->length >= item_length &&
           this->width >= item_width &&
           this->height >= item_height;
}

// just for debugging!
#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
std::ostream& operator<<(std::ostream& os, const MaximumEmptyCuboid& mec) {
    // this is how the MATLAB script expects the format to be
    os << mec.x << " " << mec.y << " " << mec.z << " "
        << mec.length << " " << mec.width << " " << mec.height << ";";
    return os;
}
#endif

/* -------------------- General utility methods -------------------- */

template<size_t array_length, size_t array_width>
void fill_occupied_space(bool occupied_space[array_length][array_width], const Cuboid & c) {
    // exclusive end
    for (int x = c.x; x < c.x + c.length; ++x) {
        for (int y = c.y; y < c.y + c.width; ++y) {
            occupied_space[x][y] = true;
        }
    }
}

// for debugging
template <size_t array_length, size_t array_width>
void dPrint_array(int verbosity, bool arr[array_length][array_width]) {
    for (int y = array_width - 1; y >= 0; --y) {
        for (int x = 0; x < array_length; ++x) {
            dPrintf(verbosity, "%c", (arr[x][y] ? 'X' : '-'));
        }
        dPrintf(verbosity, "\n");
    }
}

/* -------------------- phase 1 utility methods -------------------- */

/**
 *      v- update cache here
 *  - X - 2 1
 *  X X X 1 0
 *  X X - 0 0
 *
 * gives
 *
 *  - X 3 2 1
 *  X X 0 1 0
 *  X X 1 0 0
 *
 *  counts the number of contiguous zeros to the right
 */
template <size_t array_length, size_t array_width>
void update_cache(int cache[array_width + 1], int x,
                  bool occupied_space[array_length][array_width]) {

    for (int y = 0; y < array_width; ++y) {
        // 0 there, so increase count
        if (!occupied_space[x][y]) {
            cache[y]++;
        }
            // 1 there, so count is reset
        else {
            cache[y] = 0;
        }
    }
}

/**
 * TODO: explain why the rectangles found by find_all_MERs will only
 *   be possible to expand in the -x direction and not any other directions.
 * @param rectangles
 * @return
 */
std::vector<MaximumEmptyRectangle> remove_inner_rectangles(
        std::vector<MaximumEmptyRectangle> & rectangles) {

    // We want to group the rectangles by (urx, ury, lly), so we
    //   sort using these keys first and break ties with llx
    std::sort(rectangles.begin(), rectangles.end(), [](
            const MaximumEmptyRectangle& mer1,
            const MaximumEmptyRectangle& mer2) {
        // custom compare that sorts the rectangles lexicographically
        // in the order: lly, urx, ury, llx
        return std::tie(mer1.lly, mer1.urx, mer1.ury, mer1.llx) <
               std::tie(mer2.lly, mer2.urx, mer2.ury, mer2.llx);
    });

    std::vector<MaximumEmptyRectangle> result;
    for (const MaximumEmptyRectangle mer : rectangles) {
        // if two mers are tied by these 3 values, it means that the one we
        // are considering now has a higher llx, so it's redundant
        if (result.empty() ||
            std::tie(result.back().urx, result.back().ury, result.back().lly)
            != std::tie(mer.urx, mer.ury, mer.lly)) {
            result.push_back(mer);
        }
    }

    return result;
}

/* CO-ORDINATE SYSTEM REMINDER:
 *
 *                 w
 *       +------+  i
 *    y  |      |  d
 *    ^  O------+  t
 *    |  ^length   h
 *    |  |
 *    |   \_(x, y)
 *    +------> x
 */
/**
 * Given a boolean matrix with 0s and 1s, returns a list of
 * rectangles that satisfy two conditions:
 *  (i) every boolean in the rectangle is a 0
 *  (ii) the rectangle can't be expanded in any of
 *    the 4 possible direction without introducing a 1
 *
 * Algorithm:
 *   for each x-co-ordinate of a lower-left corner of potential rectangle:
 *     for each y-co-ordinate of a upper-right corner of potential rectangle:
 *       consider the longest possible rectangle, using a cache to determine
 *          the length
 *       if we find a larger rectangle:
 *         add the current consideration to a stack, then consider the new one
 *       if we find a smaller rectangle:
 *         this means that one or more rectangles we considered in the past can't
 *            be expanded further upwards, so unwind the stack and record them
 *         then start considering the new one
 *       don't do anything if length doesn't change
 *
 * Time complexity: O(M * N + C * lg(C)),
 *  - M is the array_length
 *  - N is the array_width
 *  - C is the number of rectangles found, **very**
 *     unlikely to be close to M * N, but in the worst
 *     case O(M * N)
 *
 * @tparam array_length size of the first dimension of occupied_space
 * @tparam array_width  size of the second dimension of occupied_space
 * @param occupied_space a boolean matrix
 * @return a std::vector of MaximumEmptyRectangles satisfying (i) and (ii)
 *      as described above.
 */
template <size_t array_length, size_t array_width>
std::vector<MaximumEmptyRectangle> find_all_maximum_empty_rectangles(
        bool occupied_space[array_length][array_width]) {
    // TODO: ...
    std::vector<MaximumEmptyRectangle> result;

    // we have an extra empty slot such that we ensure
    // that all rectangle consideration are closed
    // before terminating the loop.
    int cache[array_width + 1];
    for (int i = 0; i < array_width + 1; ++i) {
        cache[i] = 0;
    }

    // keeps track of pairs (l, y) where the top
    // of the stack gives the previous rectangle length (l)
    // we considered and at what height (y) we stopped
    // considering that length in favour of a longer one.
    std::stack<std::pair<int, int>> s;

    // start on the right because we expand cache leftwards
    for (int x = array_length - 1; x >= 0; x--) {
        dAssertHard(s.empty(), "find_all_maximum_empty_rectangles starts with an empty stack.");
        // determine content for this column
        update_cache<array_length, array_width>(cache, x, occupied_space);

        // what is the length of the current rectangle
        // we are looking at?
        int length = 0;
        for (int y = 0; y < array_width + 1; ++y) {
            // we discovered a longer rectangle, so save
            // the current state for later
            if (cache[y] > length) {
                s.push(std::pair<int, int>(length, y));
                length = cache[y];
            }
                // the rectangle we are currently considering
                // is too long, so save it as a candidate and
                // start considering shorter ones.
            else if (cache[y] < length) {
                int prevLength, y0;
                while (cache[y] < length) {
                    prevLength = s.top().first;
                    // lower y-point of rectangle
                    y0 = s.top().second;
                    s.pop();

                    // save the result
                    result.push_back({x, y0, x + length, y});

                    // revert back to considering the previous rectangle
                    length = prevLength;
                }
                // the above while-loop will remove one too-many triangles
                // if we start considering a length that has not been
                // examined before. In that case, we re-add the last
                // item that was popped.
                // The non-zero check ensures that we don't get
                // redundant MERs that can be expanded upwards (+y)
                if (cache[y] > 0 && prevLength != cache[y]) {
                    s.push(std::pair<int, int>(prevLength, y0));
                }
                length = cache[y];
            }
        }
    }
    // some MERs will be redundant
    return remove_inner_rectangles(result);
}

/* -------------------- phase 1 driver function -------------------- */

template <size_t array_length, size_t array_width>
std::vector<MaximumEmptyCuboid> find_all_maximum_empty_cuboids(
        std::vector<Cuboid> cuboids, const int box_height) {

    // sort the cuboids by z-value of top-face in ascending order
    std::sort(cuboids.begin(), cuboids.end());
    // in the first iteration of the below loop, we consider the top-face
    // of the highest item, so we don't want to add any occupying items.
    // Therefore, we add a stub empty Cuboid item.
    Cuboid temp = {0, 0, 0, 0, 0, 0};
    cuboids.push_back(temp);

    // keeps track of the XY co-ordinates we can't consider empty at some height level
    bool occupied_space[array_length][array_width];
    for (auto & x : occupied_space) {
        for (bool & y : x) {
            y = false;
        }
    }

    // this is where we store the results
    std::vector<MaximumEmptyCuboid> candidates;

    // TODO: explain base height going down....
    for (int i = cuboids.size() - 1; i >= 0; i--) {
        // this place is not empty anymore when we lower our height
        fill_occupied_space<array_length,
                array_width>(occupied_space, cuboids[i]);
        // debug occupied_space:
        dPrintf(5, "find_all_maximum_empty_cuboids: space occupied at height z=%d:\n", (i == 0 ? 0 : cuboids[i - 1].z + cuboids[i - 1].height));
        dPrint_array<array_length, array_width>(5, occupied_space);

        // if the next item has a top-face at the same height,
        // we use the solutions found after removing that item instead
        // because the ones we would find after this item would be redundant
        if (i > 0 && cuboids[i - 1].z + cuboids[i - 1].height ==
                     cuboids[i].z + cuboids[i].height) {
            continue;
        }

        // solve the 2D problem
        std::vector<MaximumEmptyRectangle> mers =
                find_all_maximum_empty_rectangles<array_length, array_width>(occupied_space);

        // the base height of the maximum empty cuboid is the
        // height of the top face of the item just below
        int base_height = 0;
        if (i > 0) {
            base_height = cuboids[i - 1].z + cuboids[i - 1].height;
        }

        dPrintf(5, "find_all_maximum_empty_cuboids: Found %zu candidates:\n", mers.size());
        for (auto & mer : mers) {
            candidates.emplace_back(mer, base_height, box_height - base_height);
            dPrintf(5, "  %d %d %d %d %d %d;\n", candidates.back().x, candidates.back().y, candidates.back().z,
                    candidates.back().length, candidates.back().width, candidates.back().height);
        }
    }

    return candidates;
}

/* -------------------- phase 2 utility methods -------------------- */


// modifies the feasible_pos array to only be true where the manipulator arm
// can fit (i.e. feasibly place the item) when z is some value
// empty_spaces = copy of candidates sorted by z in ascending order and with dummy box at height -1
//   TODO: is -1 because seperate from boxes at 0
// item_height  = height of the item to place
// TODO: optimisation, can cache results based on z since we sort by z anyways
//   so only recompute when z changes
template <size_t array_length, size_t array_width>
void compute_reachable_positions(int item_length, int item_width, int manipulator_height,
                                                     bool feasible_pos[array_length][array_width],
                                                     const std::vector<MaximumEmptyCuboid>& empty_spaces) {

    // assume no fit
    for (int x = 0; x < array_length; ++x) {
        for (int y = 0; y < array_width; ++y) {
            feasible_pos[x][y] = false;
        }
    }

    // assert mecs sorted by z in descending order
    for (int i = 0; i < empty_spaces.size(); ++i) {
        dAssertHard(i == 0 || !(BOTTOM_FACE_COMP(empty_spaces[i], empty_spaces[i - 1])),
            "compute_reachable_positions: The empty_spaces passed are sorted in ascending order");
    }

    // finds the first empty space with a base higher than the top-face of the item
    MaximumEmptyCuboid temp({0, 0, 0, 0}, manipulator_height, 0);
    auto c = std::upper_bound(empty_spaces.begin(), empty_spaces.end(), temp, BOTTOM_FACE_COMP);

    // subtracting one gives the last MEC with a height lower than manipulator_height, and this should exist
    // because of the dummy box added before invokign this function.
    dAssertHard(c != empty_spaces.begin() && !empty_spaces.empty(),
            "compute_reachable_positions: The upper_bound is valid.");

    // this cannot be the dummy box, so the - 1 is safe
    // store this height, because we only consider mecs at this height
    int mec_base_z = c[-1].z;
    dPrintf(2, "compute_reachable_positions: basing reachability at height %d on MECs with base z=%d\n",
            manipulator_height, mec_base_z);

    // we add one to round up (TODO: explain why?)
    int x_offset = std::max((ROBOT_ARM_LENGTH - item_length + 1) / 2, 0);
    int y_offset = std::max((ROBOT_ARM_WIDTH - item_width + 1) / 2, 0);

    do {
        c--;
        // make sure the xy start coordinates don't go outside the MEC
        int llx = std::min(c->x + x_offset, c->x + c->length - 1);
        int lly = std::min(c->y + y_offset, c->y + c->width  - 1);
        int urx = c->x + c->length - item_length - x_offset;
        int ury  = c->y + c->width  - item_width  - y_offset;
        // the constructor uses dimensions instead of upper right corners
        // add one because ours were inclusive
        Cuboid fill = {llx, lly, 0, urx - llx + 1, ury - lly + 1, 0};
        fill_occupied_space<array_length, array_width>(feasible_pos, fill);
    } while (c != empty_spaces.begin() && c[-1].z == mec_base_z);

    // debug print
    dPrintf(5, "The reachable positions at height %d is:\n", manipulator_height);
    dPrint_array<array_length,array_width>(5, feasible_pos);
}

/**
 * TODO: explain!
 *
 * cuboids must be sorted!
 * @param item_length
 * @param item_width
 * @param cuboids
 * @return
 */
template <size_t array_length, size_t array_width>
void compute_stable_positions(int item_length, int item_width, int base_height,
                              bool stable_positions[array_length][array_width],
                              const std::vector<Cuboid> &cuboids) {

    // base case for the box floor
    if (base_height == 0) {
        for (int x = 0; x < array_length; ++x) {
            for (int y = 0; y < array_width; ++y) {
                stable_positions[x][y] = true;
            }
        }
        return;
    }

    // assert cuboids sorted by z + height in ascending order
    for (int i = 0; i < cuboids.size(); ++i) {
        dAssertHard(i == 0 || !(cuboids[i].z + cuboids[i].height < cuboids[i - 1].z + cuboids[i - 1].height),
                "compute_stable_positions: The cuboids passed are sorted in ascending order by top-face");
    }

    // TODO: this parameter has to be the same as the other one!

    // assume no stable ground at all
    bool ground[array_length][array_width];
    for (auto & x : ground) {
        for (bool & y : x) {
            y = false;
        }
    }

    // find the first cuboid that has a top-face
    // at height equal to the MEC's z value
    Cuboid temp = {0, 0, base_height, 0, 0, 0};
    auto supportingCuboid = std::lower_bound(cuboids.begin(), cuboids.end(), temp);

    dAssertHard(supportingCuboid != cuboids.end(),
            "one or more supporting cuboids were found.");
    dAssertHard(supportingCuboid->z + supportingCuboid->height == base_height,
            "the supporting cuboid has a top-face equal to the base height");

    // iterate all the supporting cuboids, and note their supporting area
    while (supportingCuboid != cuboids.end() && supportingCuboid->z + supportingCuboid->height == base_height) {
        // fill_occupied_space
        fill_occupied_space<array_length, array_width>(ground, *supportingCuboid);
        supportingCuboid++;
    }

    dPrintf(4, "compute_stable_positions: the supporting ground at height z=%d:\n", base_height);
    dPrint_array<array_length, array_width>(4, ground);

    // sum[x][y] gives the number of 1's in the area ground[0..x][0..y] (inclusive end)
    int sum[array_length][array_width];
    for (int x = 0; x < array_length; ++x) {
        for (int y = 0; y < array_width; ++y) {
            if (x == 0 && y == 0) {
                // base case, no previously computed entries to count
                sum[x][y] = 0;
            } else if (x == 0) {
                // we use the column below
                sum[x][y] = sum[x][y - 1];
            } else if (y == 0) {
                // we use the previous row
                sum[x][y] = sum[x - 1][y];
            } else {
                // we end up counting one rectangle twice, so remove it
                sum[x][y] = sum[x - 1][y] + sum[x][y - 1] - sum[x - 1][y - 1];
            }
            // count the current entry
            sum[x][y] += ground[x][y] ? 1 : 0;
        }
    }

    dPrintf(4, "compute_stable_positions: the precomputed sums:\n");
    for (int y = array_width - 1; y >= 0; --y) {
        for (int x = 0; x < array_length; ++x) {
            // pad with 0s
            dPrintf(4, " %03d ", sum[x][y]);
        }
        dPrintf(4, "\n");
    }

    // iterate y first because we value as low y as possible
    for (int lly = 0; lly < array_width - item_width; ++lly) {
        for (int llx = 0; llx < array_length - item_length; ++llx) {
            int supportingEntries = -1;
            if (llx == 0 && lly == 0) {
                // we have already computed this case
                supportingEntries = sum[llx + item_length - 1][lly + item_width - 1];
            } else if (llx == 0) {
                // +-+ o \_ we sum this square part
                // +-+ o /
                // o o o <- and remove the rectangle below
                supportingEntries = sum[llx + item_length - 1][lly + item_width - 1]
                        - sum[llx + item_length - 1][lly - 1];
            } else if (lly == 0) {
                // symmetric to the above
                supportingEntries = sum[llx + item_length - 1][lly + item_width - 1]
                        - sum[llx - 1][lly + item_width - 1];
            } else {
                // in the general case, we subtract the lower-left subarray twice,
                // so we add it back afterwards
                supportingEntries = sum[llx + item_length - 1][lly + item_width - 1]
                                  - sum[llx + item_length - 1][lly - 1]
                                  - sum[llx - 1              ][lly + item_width - 1]
                                  + sum[llx - 1              ][lly - 1];
            }
            dAssertHard(supportingEntries >= 0, "We found a positive amount of supporting entries.");

            // is it stable
            double support_fraction = double(supportingEntries) /
                    double(item_width * item_length);
            stable_positions[llx][lly] = (support_fraction > STABILITY_SUPPORT_FRACTION);
        }
    }

    // TODO: remove this stub
//    this->stable_position = std::make_pair(5, 6);
//    this->has_computed_stable_position = true;
//    return true;
}

//std::tuple<int, int, int> MaximumEmptyCuboid::get_stable_position() {
////    return std::make_tuple(1, 2, 6);
//    if (!this->has_computed_stable_position) {
//        throw std::runtime_error("Attempt to get stable position when "
//                                 "it doesn't exist or hasn't been computed.");
//    } else {
//        return {this->stable_position.first, this->stable_position.second, this->z};
//    }
//}

/* -------------------- phase 2 driver function -------------------- */

/**
 * TODO: docs
 *
 * cuboids must be sorted in non-decreasing order by (z+height)!
 *
 * @param length
 * @param width
 * @param height
 * @param candidates
 * @param cuboids
 * @return
 */
template <size_t array_length, size_t array_width>
std::tuple<int, int, int> pick_best_candidate(
                          int length, int width, int height,
                          std::vector<MaximumEmptyCuboid> & candidates,
                          std::vector<Cuboid> & cuboids) {

    // sort the candidates first because filtering is more expensive
    std::sort(candidates.begin(), candidates.end(), HEURISTIC_COMP);

    // used to decide whether the manipulator arm can reach certain spots
    std::vector<MaximumEmptyCuboid> empty_spaces(candidates); // copy
    // We set the height to -1 to disambiguate the dummy from actual EMC at z=0
    MaximumEmptyCuboid dummy_packing_box({0,0,array_length,array_width}, -1, 0);
    empty_spaces.push_back(dummy_packing_box);
    // sort the EMSs in ascending order by their base z value
    std::sort(empty_spaces.begin(), empty_spaces.end(), BOTTOM_FACE_COMP);

    // sort the cuboids by ascending z
    std::sort(cuboids.begin(), cuboids.end());

    bool feasible_positions[array_length][array_width];
    bool stable_positions[array_length][array_width];

    dPrintf(2, "pick_best_candidate: Considering %zu different candidates:\n", candidates.size());

    // find the first candidate that works
    for (auto & candidate : candidates) {
        dPrintf(3, "  %d %d %d %d %d %d;\n", candidate.x, candidate.y, candidate.z,
                candidate.length, candidate.width, candidate.height);
        if (candidate.can_fit_item(length, width, height)) {
            dPrintf(3, "can fit item\n");
            // TODO: only recompute when candidate.z changes
            compute_reachable_positions<array_length, array_width>(length, width, candidate.z + height, feasible_positions, empty_spaces);
            compute_stable_positions<array_length, array_width>(length, width, candidate.z, stable_positions, cuboids);

            // TODO: iterate (llx, lly)s and use the first one that is both stable and reachable
            for (int lly = candidate.y; lly < candidate.y + candidate.width - width + 1; ++lly) {
                for (int llx = candidate.x; llx < candidate.x + candidate.length - length + 1; ++llx) {
                    if (stable_positions[llx][lly] && feasible_positions[llx][lly]) {
                        dPrintf(2, "pick_best_candidate: Found a candidate (%d, %d) z=%d\n", llx, lly, candidate.z);
                        return {llx, lly, candidate.z};
                    }
                }
            }
        }
    }

    dPrintf(2, "pick_best_candidate: Did not find any valid positions.\n");
    return {-1, -1, -1};
}

/* -------------------- main driver function -------------------- */

bool process_optimiser_main(const double * box_points,
                            const double * item_points,
                            const int item_points_size,
                            const double * item_indices, // ?
                            const int item_indices_size,
                            double * tetromino_dimensions,
                            double * tetromino_position) {
    // Reset assertion counter
    ASSERTION_FAILURES = 0;

    // assume the first co-ordinate is the lower one,                    !
    // second co-ordinate is the higher one
    PackingBox pb = {box_points[0], box_points[4], box_points[2],
                     box_points[3] - box_points[0],
                     box_points[4] - box_points[1],
                     box_points[5] - box_points[2]};

    dPrintf(2, "process_optimiser_main: packing box corner at (%f, %f, %f) and dimensions [%f %f %f]\n",
        pb.x, pb.y, pb.z, pb.length, pb.width, pb.height);

    std::vector<Cuboid> cuboids;

    // iterate the items in the box
    for (int i = 0; i < item_indices_size; ++i) {
        int item_id = floor(item_indices[i] + 0.5);
        int next_item_id;
        // we are at last item, so set bound to number of points
        if (i == item_indices_size - 1) {
            next_item_id = item_points_size;
        } else {
            next_item_id = floor(item_indices[i + 1] + 0.5);
        }
        // iterate the points while finding the lowest and highest of each co-ordinate
        double lx = 1000000, ly = 1000000, lz = 1000000, ux = -1000000, uy = -1000000, uz = -1000000;
        for (int j = item_id; j < next_item_id; j += 3) {
            // x co-ordinate
            lx = std::min(lx, item_points[j]);
            ux = std::max(ux, item_points[j]);
            // y co-ordinate
            ly = std::min(ly, item_points[j + 1]);
            uy = std::max(uy, item_points[j + 1]);
            // z co-ordinate
            lz = std::min(lz, item_points[j + 2]);
            uz = std::max(uz, item_points[j + 2]);
        }

        // create the bounding box
        BoxTetromino bt(lx, pb.y + (pb.y - uy), lz, ux - lx, uy - ly, uz - lz, pb);
        // endgame quick fixes:
        if (bt.z < 0) {
            ASSERTION_FAILURES--;
            bt.z = 0;
        }
        if (bt.x < 0) {
            ASSERTION_FAILURES--;
            bt.x = 0;
        }
        if (bt.y < 0) {
            ASSERTION_FAILURES--;
            bt.y = 0;
        }
        cuboids.push_back(bt);
    }

    // convert item to be packed to the virtual co-ordinate system
    Cuboid tetromino = BoxTetromino(pb.x, pb.y, pb.z,
                                    tetromino_dimensions[0],
                                    tetromino_dimensions[1],
                                    tetromino_dimensions[2], pb);

    // debug what we've set up
    dPrintf(2, "process_optimiser_main: using virtual co-ordinate system with dimensions: %d x %d x %d\n",
            MER_LENGTH_GRANULARITY, MER_WIDTH_GRANULARITY, MER_HEIGHT_GRANULARITY);
    dPrintf(2, "Found %zu items currently in the box:\n", cuboids.size());
    for (Cuboid &c : cuboids) {
        dPrintf(2, "  %d %d %d %d %d %d;\n", c.x, c.y, c.z, c.length, c.width, c.height);
    }
    dPrintf(2, "process_optimiser_main: Attempting to place cuboid with dimensions l=%d, w=%d, h=%d\n",
            tetromino.length, tetromino.width, tetromino.height);

    if (ASSERTION_FAILURES > 0) {
        dPrintf(1, "Found %d assertion failures. Stopping the simulation...\n", ASSERTION_FAILURES);
        return false; //throw "STOP";
    }

    dPrintf(2, "process_optimiser_main: Running phase 1 of the algorithm...\n");

    // run phase 1 of the algorithm
    std::vector<MaximumEmptyCuboid> candidates =
            find_all_maximum_empty_cuboids<MER_LENGTH_GRANULARITY, MER_WIDTH_GRANULARITY>(cuboids, MER_HEIGHT_GRANULARITY);
    dPrintf(2, "process_optimiser_main: Running phase 2 of the algorithm...\n");
    // run phase 2 of the algorithm
    std::tuple<int, int, int> best_cand =
            pick_best_candidate<MER_LENGTH_GRANULARITY, MER_WIDTH_GRANULARITY>(tetromino.length, tetromino.width,
                                                                               tetromino.height, candidates, cuboids);

    dPrintf(2, "process_optimiser_main: Found solution (%d, %d, %d)\n",
            std::get<0>(best_cand), std::get<1>(best_cand), std::get<2>(best_cand));

    // convert the resulting co-ordinates back to the simulink co-ordinate system
    tetromino_position[0] = double(std::get<0>(best_cand)) * pb.length / double(MER_LENGTH_GRANULARITY) + pb.x;
    tetromino_position[1] = double(std::get<1>(best_cand)) * pb.width / double(MER_WIDTH_GRANULARITY) + box_points[1];
    tetromino_position[2] = double(std::get<2>(best_cand)) * pb.height / double(MER_HEIGHT_GRANULARITY) + pb.z;

    dPrintf(2, "process_optimiser_main: Returning position (%f, %f, %f)\n",
            tetromino_position[0], tetromino_position[1], tetromino_position[2]);

    // return true if the item fits
    if (tetromino_position[0] == -1) {
        return false;
    } else {
        return true;
    }
}

#define MAIN 0

#if (MAIN==1)
int main() {
    double box_points[] = {-2, -2, -2, 8, 8, 8};
    double item_points[] = {-1, -1, 0, 2, 2, 2};
    double item_indices[] = {0};
    double tetr_dims[] = {4, 4, 4};
    double result[3];

    process_optimiser_main(box_points, item_points, 6, item_indices, 1, tetr_dims, result);

    printf("%f %f %f\n", result[0], result[1], result[2]);
    return 0;
}
#endif

#if (MAIN==2)
int main() {
    std::vector<Cuboid> cuboids;

    // test packing items
    Cuboid c1 = {-1, -1, -1, 10, 20, 10};
    Cuboid c2 = {-1, -1, -1, 30, 50, 40};
    Cuboid c3 = {-1, -1, -1, 5, 5, 10};
    Cuboid c4 = {-1, -1, -1, 25, 25, 20};
    Cuboid c5 = {-1, -1, -1, 25, 25, 20};
    Cuboid c6 = {-1, -1, -1, 25, 25, 20};
    Cuboid c7 = {-1, -1, -1, 25, 25, 20};
    Cuboid c8 = {-1, -1, -1, 50, 20, 30};
    Cuboid c9 = {-1, -1, -1, 10, 50, 60};
    Cuboid c10 = {-1, -1, -1, 10, 10, 10};

//    Cuboid c1 = {-1, -1, -1, 12, 12, 12};
//    Cuboid c2 = {-1, -1, -1, 50, 50, 50};
//    Cuboid c3 = {-1, -1, -1, 30, 30, 30};
//    Cuboid c4 = {-1, -1, -1, 30, 30, 30};
//    Cuboid c5 = {-1, -1, -1, 40, 40, 40};
//    Cuboid c6 = {-1, -1, -1, 20, 20, 40};
//    Cuboid c7 = {-1, -1, -1, 40, 40, 60};
//    Cuboid c8 = {-1, -1, -1, 40, 60, 30};
//    Cuboid c9 = {-1, -1, -1, 10, 10, 10};
//    Cuboid c10 = {-1, -1, -1, 50, 50, 5};
    std::vector<Cuboid> items = {c1, c2, c3, c4, c5, c6, c7, c8, c9, c10};

    for (int i = 0; i < items.size(); ++i) {
        std::vector<MaximumEmptyCuboid> candidates = find_all_maximum_empty_cuboids<100, 100>(cuboids, 100);
        std::tuple<int, int, int> sol = pick_best_candidate<100, 100>(items[i].length, items[i].width, items[i].height, candidates, cuboids);
        items[i].x = std::get<0>(sol);
        items[i].y = std::get<1>(sol);
        items[i].z = std::get<2>(sol);
        cuboids.push_back(items[i]);
        printf("%d %d %d %d %d %d;\n", items[i].x, items[i].y, items[i].z, items[i].length, items[i].width, items[i].height);
    }
}
#endif

//#ifdef GET_FULL_PROCESS_OPTIMISER_HEADER
//int main() {
//    double box_points[] = {0,0,0,10,10,10};
//    double item_points[] = {10,10,0,20,20,10,30,30,30,40,40,40};
//    double item_indices[] = {1, 7};
//
//    double result[3];
//    process_optimiser_main(box_points, item_points, 12, item_indices, 2, result);
////    printf("%f %f %f\n", result[0], result[1], result[2]);
//
////    std::vector<Cuboid> cubes;
////    cubes.push_back({0, 0, 0, 10, 10, 15});
////    cubes.push_back({20, 0, 0, 10, 10, 11});
////    std::vector<MaximumEmptyCuboid> mecs = find_all_maximum_empty_cuboids<25, 25>(cubes, 25);
////    // TODO: add below code to driver function
////    MaximumEmptyCuboid packing_box({0,0,25,25}, -1, 0);
////    mecs.push_back(packing_box);
////    std::sort(mecs.begin(), mecs.end(), MaximumEmptyCuboid::get_bottom_face_comp());
////
////    for (auto &cube : mecs) {
////        std::cout << cube << std::endl;
////        bool feas[25][25];
////        cube.compute_reachable_positions<25, 25>(5, 5, 10, feas, mecs, 1);
////        for (int y = 24; y >= 0; y--) {
////            for (int x = 0; x < 25; ++x) {
////                std::cout << (feas[x][y] ? "x" : "-");
////            }
////            std::cout << std::endl;
////        }
////    }
//
//
//    return 0;
//}
//#endif

// TODO: add method for finding (llx, lly) and (urx, ury) that are feasable to
//   actually place the item in:
//   * given candidates, to binary search to find the ones with z being just lower or
//     equal to height of face of this one were we place it in this MEC
//   * iterate these ones to find the above co-ords, use the one with lowest llx, lly
//     and then use the urx, ury of this one regardless of the ur position (or else
//     too complex *sigh*)
//   * special case when actual item larger than the robot bounding box
//   All this is passed to the stability checker which limits itself checking these spots



//// Put hacks for template usage in unit tests here
bool occupied[4][4];
std::vector<MaximumEmptyRectangle> temp = find_all_maximum_empty_rectangles<4, 4>(occupied);
// ...
