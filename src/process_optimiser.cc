#include <iostream>
#include <algorithm>
#include <tuple>
#include <stack>
#include <utility>
#include "process_optimiser.h"


/** ---------------------- CLASS STUFF ------------------------------------ */

bool MaximumEmptyCuboid::operator < (const MaximumEmptyCuboid & other) const {
    // TODO: implement properly
    if (other.z < this->z)
        return false;
    else
        return true;
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

std::ostream& operator<<(std::ostream& os, const MaximumEmptyCuboid& mec) {
//    os << "(" << mec.x << ", " << mec.y << ", " << mec.z
//        << ") dim=[" << mec.length << ", " << mec.width
//        << ", " << mec.height << "]";
    os << mec.x << " " << mec.y << " " << mec.z << " "
        << mec.length << " " << mec.width << " " << mec.height << ";";
    return os;
}

bool MaximumEmptyCuboid::has_stable_position(int item_length, int item_width, double z,
                                             const std::vector<MaximumEmptyCuboid> &candidates) {
    // TODO: initialise
    bool ground[STABILITY_LENGTH_GRANULARITY][STABILITY_WIDTH_GRANULARITY];

    // TODO: iterate all items at top face within some error of z
    // TODO: optimisation -- use std::lower_bound to find first item faster
    for (int i = 0; i < 10; i++) {
        // fill_occupied_space(ground, c);
    }

    int C[STABILITY_LENGTH_GRANULARITY][STABILITY_WIDTH_GRANULARITY];

    // TODO: precompute sums of 1s in C

    // TODO: iterate lower left corners
    // TODO: if within some error, return true and modify solution co-ords

    // TODO: remove this stub
    this->stable_position = std::make_pair(5, 6);
    this->has_computed_stable_position = true;
    return true;
}

std::tuple<int, int, int> MaximumEmptyCuboid::get_stable_position() {
    if (!this->has_computed_stable_position) {
        throw std::runtime_error("Attempt to get stable position when "
                                 "it doesn't exist or hasn't been computed.");
    } else {
        return std::tuple<int, int, int>(this->stable_position.first,
                                         this->stable_position.second, this->z);
    }
}

bool MaximumEmptyCuboid::can_fit_item(int item_length, int item_width, double item_height) {
    // TODO: implement
    return false;
}

BoxTetromino::BoxTetromino(double x, double y, double z,
                           double l, double w, double h, const PackingBox & pb) :
    real_x(x), real_y(y), real_z(z), real_length(l), real_width(w), real_height(h) {
    // TODO: initialize super fields based on this info
    this->x = 0;
    this->y = 0;
    this->z = 0.0;
    // TODO: ...
}

/** ------------------------------ utilies ---------------------------------*/

template<size_t array_length, size_t array_width>
void fill_occupied_space(bool occupied_space[array_length][array_width],
                         const Cuboid & c) {
    for (int x = c.x; x < c.x + c.length; ++x) {
        for (int y = c.y; y < c.y + c.width; ++y) {
            occupied_space[x][y] = true;
        }
    }
}

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
        std::vector<Cuboid> cuboids, const PackingBox & pb) {

    // TODO: move sort routuine out
    // sort the cuboids by z-value of top-face in ascending order
    std::sort(cuboids.begin(), cuboids.end(), [](
                      const Cuboid& cube1, const Cuboid& cube2) {
        return cube1.z + cube1.height < cube2.z + cube2.height;
    });
    // in the first iteration of the below loop, we consider the top-face
    // of the highest item, so we don't want to add any occupying items.
    // Therefore, we add a stub empty Cuboid item.
    cuboids.push_back({0, 0, 0, 0, 0, -1});

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
            candidates.emplace_back(mer, base_height, pb.height - base_height);
        }
    }

    return candidates;
}

/** ------------------------------ phase 2 ---------------------------------*/

std::tuple<double, double, double> pick_best_candidate(
                          int length, int width, int height,
                          std::vector<MaximumEmptyCuboid> candidates) {

    // sort the candidates first because filtering is more expensive
    std::sort(candidates.begin(), candidates.end());
    // TODO: copy of candidates sorted by z for has_stable_position?

    // find the first candidate that works
    for (auto c = candidates.begin(); c != candidates.end(); c++) {
        // TODO: check if item fits, class method

        // TODO: check if item has stable position, if so use it,
        //  cast things to doubles, and return
        c->has_stable_position(length, width, height, candidates);
    }

    // TODO: remove stub
    if (!candidates.empty())
        return candidates[0].get_stable_position();
    else
        return std::make_tuple(-1.0, -1.0, -1.0);
}

/** ------------------------------ driver ----------------------------------*/

// call with
// coder.ceval("process_optimiser_main",
//      box_points, item_points, len(item_points),
//      item_indices, len(item_indices),
//      coder.wref(result));
bool process_optimiser_main(const double * box_points,
                            const double * item_points,
                            const int item_points_size,
                            const int * item_indices,
                            const int item_indices_size,
                            double * tetromino_position) {

    // TODO: construct box object
    PackingBox test_pb = {0, 0, 0, 1000, 1000, 1000};

    // TODO: construct cuboids from the given information
    // TODO: make method that does this using the point clouds given

    // TODO: remove stub
    std::vector<Cuboid> cuboids;
    BoxTetromino bt_test(8, 4, 0, 10, 10, 20, test_pb);
    cuboids.push_back(bt_test);

    debug("Got here");

    // find all candidates
    std::vector<MaximumEmptyCuboid> candidates = find_all_maximum_empty_cuboids<MER_LENGTH_GRANULARITY, MER_WIDTH_GRANULARITY>(cuboids, test_pb);

    // pick the best one
    std::tuple<int, int, int> sol = pick_best_candidate(10, 5, 8, candidates);

    tetromino_position[0] = double(std::get<0>(sol));
    tetromino_position[1] = double(std::get<1>(sol));
    tetromino_position[2] = double(std::get<2>(sol));

    return true;
}

// for testing the code within the IDE
int main() {
    double box_pos[3] = {0, 0, 0};
    double box_dim[3] = {1000, 1000, 1000};
    double result[3];

//    process_optimiser_main(box_pos, box_dim, result);

//    std::cout << "Resulting position:" << std::endl
//            << "\tx: " << result[0] << std::endl
//            << "\ty: " << result[1] << std::endl
//            << "\tz: " << result[2] << std::endl;

    // --x-
    // --xx
    // --xx
    // --x-
    bool occupied1[4][4] = {
            {1, 1, 1, 1},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {1, 0, 0, 1}
    };

    //    /--- trouble case
    //   v
    // xxx--
    // xxxxx
    // xx--x
    // xxxxx
    // -xxxx
    bool occupied2[5][5] = {
            {1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 1},
            {0, 0, 0, 0, 1}
    };

    // ---X
    // --XX
    // -XXX
    // ---X
    bool occupied3[4][4] = {
            {1, 1, 1, 1},
            {1, 0, 1, 1},
            {1, 0, 0, 1},
            {0, 0, 0, 0}
    };


    // 00000000000000
    // 00110000000000
    // 00110000000000
    // 00110011111100
    // 00000011111100
    // 00000011111100
    // 00000011111100
    // 00000000000000
    // 00000000000000
    // 00000000000000
    bool occupied4[14][10] = {
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,1,1,1,0},
            {0,0,0,0,0,0,1,1,1,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,1,1,1,1,0,0,0},
            {0,0,0,1,1,1,1,0,0,0},
            {0,0,0,1,1,1,1,0,0,0},
            {0,0,0,1,1,1,1,0,0,0},
            {0,0,0,1,1,1,1,0,0,0},
            {0,0,0,1,1,1,1,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0}
    };

//    std::vector<MaximumEmptyRectangle> rects =
//            find_all_maximum_empty_rectangles<14, 10>(occupied4);
//    for (MaximumEmptyRectangle r : rects) {
//        printf("(%d, %d), (%d, %d)\n", r.llx, r.lly, r.urx, r.ury);
//    }

    PackingBox test_pb = {0, 0, 0, 100, 100, 100};
    Cuboid cube1 = {50, 50, 0, 10, 10, 10};
    Cuboid cube2 = {10, 10, 50, 10, 10, 10};
    std::vector<Cuboid> cubes = {cube1, cube2};

    std::vector<MaximumEmptyCuboid> results = find_all_maximum_empty_cuboids<100, 100>(cubes, test_pb);
    for (MaximumEmptyCuboid mec : results) {
        std::cout << mec << std::endl;
    }

    return 0;
}