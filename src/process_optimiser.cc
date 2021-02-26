#include <iostream>
#include <algorithm>
#include <tuple>
#include <stack>
#include <cmath>
#include <utility>
#include "process_optimiser.h"
#define NDEBUG
#include <cassert>

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
                           double l, double w, double h, const PackingBox & pb) :
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
    // Do assertions
    assert(this->x >= 0 && this->x < MER_LENGTH_GRANULARITY && "computed x value is out of bounds.");
    assert(this->y >= 0 && this->y < MER_LENGTH_GRANULARITY && "computed y value is out of bounds.");
    assert(this->z >= 0 && this->z < MER_LENGTH_GRANULARITY && "computed z value is out of bounds.");
    assert(this->x + this->length < MER_LENGTH_GRANULARITY && "computed length in x-dimension is out of bounds.");
    assert(this->length > 0 && "the cuboid has a zero or lower length");
    assert(this->y + this->width < MER_LENGTH_GRANULARITY && "computed width in y-dimension is out of bounds.");
    assert(this->width > 0 && "the cuboid has a zero or lower width");
    assert(this->z + this->height < MER_LENGTH_GRANULARITY && "computed height in z-dimension is out of bounds.");
    assert(this->height > 0 && "the cuboid has a zero or lower height");

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

#define BOTTOM_FACE_COMP [](const MaximumEmptyCuboid &cube1, const MaximumEmptyCuboid &cube2) { return cube1.z < cube2.z; }
//auto MaximumEmptyCuboid::get_bottom_face_comp() {
//    return [](const MaximumEmptyCuboid &cube1, const MaximumEmptyCuboid &cube2) {
//        return cube1.z < cube2.z;
//    };
//}

#define HEURISTIC_COMP [](const MaximumEmptyCuboid& cube1, const MaximumEmptyCuboid& cube2) { if (std::tie(cube1.z, cube1.y, cube1.x) == std::tie(cube2.z, cube2.y, cube2.x)) { return (cube1.z * cube1.y * cube1.x) < (cube2.z * cube2.y * cube2.x); } else { return std::tie(cube1.z, cube1.y, cube1.x) < std::tie(cube2.z, cube2.y, cube2.x); } }
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

/* -------------------- Utility methods -------------------- */

template<size_t array_length, size_t array_width>
void fill_occupied_space(bool occupied_space[array_length][array_width], const Cuboid & c) {
    // exclusive end
    for (int x = c.x; x < c.x + c.length; ++x) {
        for (int y = c.y; y < c.y + c.width; ++y) {
            occupied_space[x][y] = true;
        }
    }
}

// TODO: continue refactoring from here, go through calls to fill_occupied_space and verify down_scale_modifier

//// Utility methods -------------------------------------------------------------------

// modifies the feasible_pos array to only be true where the manipulator arm
// can fit (i.e. feasibly place the item) when z is some value (TODO: add as argument)
// empty_spaces = copy of candidates sorted by z in ascending order and with dummy box at height -1
//   TODO: is -1 because seperate from boxes at 0
// item_height  = of the item to place
// TODO: don't make as member function since only need base height of item
// TODO: optimisation, can cache results based on z since we sort by z anyways
//   so only recompute when z changes
template <size_t array_length, size_t array_width>
void compute_reachable_positions(int item_length, int item_width, int manipulator_height,
                                                     bool feasible_pos[array_length][array_width],
                                                     const std::vector<MaximumEmptyCuboid>& empty_spaces,
                                                     int downscale_multiplier) {

    // assume no fit
    for (int x = 0; x < array_length; ++x) {
        for (int y = 0; y < array_width; ++y) {
            feasible_pos[x][y] = false;
        }
    }

    // TODO: make a new copy of mecs and add dummy whole box, then sort in increasing z
    // add the box as a temporary mec because we consider that one if none else found

    // assert mecs sorted by z in descending order TODO: remove this check
    for (int i = 0; i < empty_spaces.size(); ++i) {
        debug("mec " << i << ": " << empty_spaces[i]);
//        if (i != 0 && compare(mecs[i], mecs[i - 1])*/) {
//            throw std::runtime_error("the mecs aren't sorted in ascending order!");
//        }
    }

    // finds the first empty space with a base higher than the top-face of the item
    MaximumEmptyCuboid temp({0, 0, 0, 0}, manipulator_height, 0);
    auto c = std::upper_bound(empty_spaces.begin(), empty_spaces.end(), temp, BOTTOM_FACE_COMP);

    // subtracting one gives the last MEC with a height lower than manipulator_height

    debug(manipulator_height << " gives " << (c[-1]));

    // this cannot be the dummy box, so the - 1 is safe
    // store this height, because we only consider mecs at this height
    int mec_base_z = c[-1].z;

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
//        printf("coords: %d %d %d %d\n", llx, lly, urx, ury);
//        printf("fill: (%d %d) l=%d w=%d\n", fill.x, fill.y, fill.length, fill.width);
        fill_occupied_space<array_length, array_width>(feasible_pos, fill);
    } while (c != empty_spaces.begin() && c[-1].z == mec_base_z);

    // remove the temp packing box
//    mecs.pop_back();
    // TODO: test this stuff

    // TODO: debug print
    if (manipulator_height == 10) {
        debug("here");
        for (int y = array_width - 1; y >= 0; y--) {
            for (int x = 0; x < array_length; ++x) {
                debug2(feasible_pos[x][y] ? "x" : "-");
            }
            debug("");
        }
    }
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
void compute_stable_positions(int item_length, int item_width, int base_height, bool stable_positions[array_length][array_width],
                                                  const std::vector<Cuboid> &cuboids, int downscale_multiplier) {

    // TODO: remove stub
    for (int x = 0; x < array_length; ++x) {
        for (int y = 0; y < array_width; ++y) {
            stable_positions[x][y] = true;
        }
    }
    return;

    // base case, box floor is supporting TODO: remove hack
//    if (true || this->z == 0) {
//        this->has_computed_stable_position = true;
//        this->stable_position = std::pair<int, int>(this->x, this->y);
//        return true;
//    }

    // TODO: this parameter has to be the same as the other one!

    // initialise 2d array to all false
    bool ground[STABILITY_LENGTH_GRANULARITY][STABILITY_WIDTH_GRANULARITY];
    for (auto & x : ground) {
        for (bool & y : x) {
            y = false;
        }
    }

    // find the first cuboid that has a top-face
    // at height equal to the MEC's z value
    Cuboid temp = {0, 0, base_height, 0, 0, 0};
    auto supportingCuboid = std::lower_bound(cuboids.begin(), cuboids.end(), temp);

    // iterate all the supporting cuboids, and note their supporting area
    while (supportingCuboid != cuboids.end() && supportingCuboid->z + supportingCuboid->height == base_height) {
        // fill_occupied_space
        fill_occupied_space<STABILITY_LENGTH_GRANULARITY, STABILITY_WIDTH_GRANULARITY>(ground, *supportingCuboid);
    }

    // sum[x][y] gives the number of 1's in the area ground[0..x][0..y] (inclusive end)
    int sum[STABILITY_LENGTH_GRANULARITY][STABILITY_WIDTH_GRANULARITY];
    // TODO: precompute sums of 1s in C
    for (int x = 0; x < STABILITY_LENGTH_GRANULARITY; ++x) {
        for (int y = 0; y < STABILITY_WIDTH_GRANULARITY; ++y) {
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

    // TODO: iterate lower left corners
    // TODO: if within some error, return true and modify solution co-ords

    // iterate y first because we value as low y as possible
    for (int lly = 0; lly < STABILITY_WIDTH_GRANULARITY; ++lly) {
        for (int llx = 0; llx < STABILITY_LENGTH_GRANULARITY; ++llx) {
            //    C[x+w,y+l] - C[x+w, y] - C[x, y+l] + C[x, y]
            // TODO: boundary cases *sigh*
//            int supporting_entries =
//                    sum[this->x + this->length - 1][this->y + this->width - 1]
//                    - sum[this->x + this->length - 1][this->y - 1]
//                    - sum[this->x - 1][this->y + this->width - 1]
//                    + sum[this->x - 1][this->y - 1];
//            // TODO: work from here
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



/** ------------------------------ utilies ---------------------------------*/


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
        if (!s.empty()) {
            throw std::runtime_error("find_all_maximum_empty_rectangles"
                                     " starts with a non-empty stack. This"
                                     " should not happen.");
        }
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
                if (cache[y] > 0 && prevLength != cache[y]) {
                    s.push(std::pair<int, int>(prevLength, y0));
                }
                length = cache[y];
            }
        }
    }
    return remove_inner_rectangles(result);
}

/** ------------------------------ phase 1 ---------------------------------*/

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

//    printf("%d %d %d %d %d %d\n", cuboids[0].x, cuboids[0].y, cuboids[0].z, cuboids[0].length, cuboids[0].width, cuboids[0].height);

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
        // this place is not empty anymore when we lower out height
        fill_occupied_space<array_length,
            array_width>(occupied_space, cuboids[i]);
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

        for (auto & mer : mers) {
            candidates.emplace_back(mer, base_height, box_height - base_height);
        }
    }

    return candidates;
}

/** ------------------------------ phase 2 ---------------------------------*/

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

    // sort the candidates first because filtering is more expensive TODO: what is it sorted by?
    std::sort(candidates.begin(), candidates.end(), HEURISTIC_COMP);
    // TODO: copy of candidates sorted by z for compute_stable_positions?

    // used to decide whether the manipulator arm can reach certain spots
    std::vector<MaximumEmptyCuboid> empty_spaces(candidates);
    // We set the height to -1 to disambiguate the dummy from actual EMC at z=0
    MaximumEmptyCuboid dummy_packing_box({0,0,array_length,array_width}, -1, 0);
    empty_spaces.push_back(dummy_packing_box);
    // sort the EMSs in ascending order by their base z value
    std::sort(empty_spaces.begin(), empty_spaces.end(), BOTTOM_FACE_COMP);

    // sort the cuboids by ascending z
    std::sort(cuboids.begin(), cuboids.end());

    // TODO: magic value clean-up
    bool feasible_positions[array_length][array_width];
    bool stable_positions[array_length][array_width];

    // find the first candidate that works
    for (auto & candidate : candidates) {
        if (candidate.can_fit_item(length, width, height)) {
            // TODO: only recompute when candidate.z changes
            compute_reachable_positions<array_length, array_width>(length, width, candidate.z + height, feasible_positions, empty_spaces, 1);
            compute_stable_positions<array_length, array_width>(length, width, candidate.z, stable_positions, cuboids, 1);

            // TODO: iterate (llx, lly)s and use the first one that is both stable and reachable
            for (int lly = candidate.y; lly < candidate.y + candidate.width - width + 1; ++lly) {
                for (int llx = candidate.x; llx < candidate.x + candidate.length - length + 1; ++llx) {
                    if (stable_positions[llx][lly] && feasible_positions[llx][lly]) {
                        return {llx, lly, candidate.z};
                    }
                }
            }

//            candidate.compute_stable_positions(length, width, cuboids);
//            std::cout << candidate << std::endl;
//            return candidate.get_stable_position();
        }
        // TODO: check if item fits, class method

        // TODO: check if item has stable position, if so use it,
        //  cast things to doubles, and return
//        c->compute_stable_positions(length, width, height, candidates);
    }

    return {-1, -1, -1};

    // TODO: remove stub
//    if (!candidates.empty())
//        return candidates[0].get_stable_position();
//    else
//        return std::make_tuple(-1.0, -1.0, -1.0);
}

/* ---------- driver utility methods ---------- */

/** ------------------------------ driver ----------------------------------*/

// call with
// coder.ceval("process_optimiser_main",
//      box_points, item_points, len(item_points),
//      item_indices, len(item_indices),
//      tetromino_dimensions,
//      coder.wref(result));
bool process_optimiser_main(const double * box_points,
                            const double * item_points,
                            const int item_points_size,
                            const double * item_indices, // ?
                            const int item_indices_size,
                            double * tetromino_dimensions,
                            double * tetromino_position) {

    // assume the first co-ordinate is the lower one,
    // second co-ordinate is the higher one
    PackingBox pb = {box_points[0], box_points[1], box_points[2],
                     box_points[3] - box_points[0],
                     box_points[4] - box_points[1],
                     box_points[5] - box_points[2]};

    std::vector<Cuboid> cuboids;

    // iterate the items in the box
    for (int i = 0; i < item_indices_size; ++i) {
        int item_id = item_indices[i];
        int next_item_id;
        // we are at last item, so set bound to number of points
        if (i == item_indices_size - 1) {
            next_item_id = item_points_size;
        } else {
            next_item_id = item_indices[i + 1];
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
        BoxTetromino bt(lx, ly, lz, ux - lx, uy - ly, uz - lz, pb);
        cuboids.push_back(bt);
    }

    // convert item to be packed to the virtual co-ordinate system
    Cuboid tetromino = BoxTetromino(pb.x, pb.y, pb.z,
                                    tetromino_dimensions[0],
                                    tetromino_dimensions[1],
                                    tetromino_dimensions[2], pb);

    // run phase 1 of the algorithm
    std::vector<MaximumEmptyCuboid> candidates =
            find_all_maximum_empty_cuboids<MER_LENGTH_GRANULARITY, MER_WIDTH_GRANULARITY>(cuboids,
                                                                                          MER_HEIGHT_GRANULARITY);
    // run phase 2 of the algorithm
    std::tuple<int, int, int> best_cand =
            pick_best_candidate<MER_LENGTH_GRANULARITY, MER_WIDTH_GRANULARITY>(tetromino.length, tetromino.width,
                                                                               tetromino.height, candidates, cuboids);

    // convert the resulting co-ordinates back to the simulink co-ordinate system
    tetromino_position[0] = double(std::get<0>(best_cand)) * pb.length / double(MER_LENGTH_GRANULARITY) + pb.x;
    tetromino_position[1] = double(std::get<1>(best_cand)) * pb.width / double(MER_WIDTH_GRANULARITY) + pb.y;
    tetromino_position[2] = double(std::get<2>(best_cand)) * pb.height / double(MER_HEIGHT_GRANULARITY) + pb.z;

    // return true if the item fits
    if (tetromino_position[0] == -1) {
        return false;
    } else {
        return true;
    }
}

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

//int main() {
//    // TODO: construct box object
//    PackingBox test_pb = {0, 0, 0, 40, 40, 100};
//
//    // TODO: construct cuboids from the given information
//    // TODO: make method that does this using the point clouds given
//
//    // TODO: remove stub
//    std::vector<Cuboid> cuboids;
//
//    // test packing items
//    Cuboid c1 = {-1, -1, -1, 10, 10, 50};
//    Cuboid c2 = {-1, -1, -1, 10, 10, 50};
//    Cuboid c3 = {-1, -1, -1, 10, 10, 50};
//    Cuboid c4 = {-1, -1, -1, 20, 20, 50};
//    Cuboid c5 = {-1, -1, -1, 10, 10, 50};
//    Cuboid c6 = {-1, -1, -1, 40, 40, 50};
//    Cuboid c7 = {-1, -1, -1, 10, 10, 50};
//    Cuboid c8 = {-1, -1, -1, 10, 10, 50};
//    Cuboid c9 = {-1, -1, -1, 10, 10, 50};
//    Cuboid c10 = {-1, -1, -1, 10, 10, 10};
//
////    Cuboid c1 = {-1, -1, -1, 12, 12, 12};
////    Cuboid c2 = {-1, -1, -1, 50, 50, 50};
////    Cuboid c3 = {-1, -1, -1, 30, 30, 30};
////    Cuboid c4 = {-1, -1, -1, 30, 30, 30};
////    Cuboid c5 = {-1, -1, -1, 40, 40, 40};
////    Cuboid c6 = {-1, -1, -1, 20, 20, 40};
////    Cuboid c7 = {-1, -1, -1, 40, 40, 60};
////    Cuboid c8 = {-1, -1, -1, 40, 60, 30};
////    Cuboid c9 = {-1, -1, -1, 10, 10, 10};
////    Cuboid c10 = {-1, -1, -1, 50, 50, 5};
//    std::vector<Cuboid> items = {c1, c2, c3, c4, c5, c6, c7, c8, c9, c10};
////    BoxTetromino bt_test(1, 1, 1, 12, 12, 20, test_pb);
////    cuboids.push_back(bt_test);
//
//    for (int i = 0; i < items.size(); ++i) {
//        std::vector<MaximumEmptyCuboid> candidates = find_all_maximum_empty_cuboids<100, 100>(cuboids, 100);
//        std::tuple<int, int, int> sol = pick_best_candidate<100, 100>(items[i].length, items[i].width, items[i].height, candidates, cuboids);
//        items[i].x = std::get<0>(sol);
//        items[i].y = std::get<1>(sol);
//        items[i].z = std::get<2>(sol);
//        cuboids.push_back(items[i]);
//        printf("%d %d %d %d %d %d;\n", items[i].x, items[i].y, items[i].z, items[i].length, items[i].width, items[i].height);
//    }
//    // find all candidates
////    std::vector<MaximumEmptyCuboid> candidates = find_all_maximum_empty_cuboids<MER_LENGTH_GRANULARITY, MER_WIDTH_GRANULARITY>(cuboids, test_pb.height);
//
//    // pick the best one
////    std::tuple<int, int, int> sol = pick_best_candidate<40, 40>(20, 20, 20, candidates, cuboids);
//
////    tetromino_position[0] = double(std::get<0>(sol));
////    tetromino_position[1] = double(std::get<1>(sol));
////    tetromino_position[2] = double(std::get<2>(sol));
//
//    return true;
//}

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
