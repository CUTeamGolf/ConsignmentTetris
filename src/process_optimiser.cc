#include <utility>
#include <algorithm>
#include <tuple>
#include "process_optimiser.h"

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
    // TODO: ...
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
    return false;
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
    // TODO: ...
}

std::vector<MaximumEmptyRectangle> find_all_maximum_empty_rectangles(
        bool occupied_space[MER_LENGTH_GRANULARITY][MER_WIDTH_GRANULARITY]) {
    // TODO: ...

    // TODO: remove stub
    std::vector<MaximumEmptyRectangle> result;
    result.push_back({1, 1, 10, 10});
    return result;
}

/** ------------------------------ phase 1 ---------------------------------*/

std::vector<MaximumEmptyCuboid> find_all_maximum_empty_cuboids(
        std::vector<Cuboid> cuboids, const PackingBox & pb) {

    // TODO: sort cuboids by z + h

    bool occupied_space[MER_LENGTH_GRANULARITY][MER_WIDTH_GRANULARITY];
    std::vector<MaximumEmptyCuboid> candidates;

    // TODO: add initial iteration with no obstacles
    // TODO: make sure correct height looked at, not height of *c

    for (auto c = cuboids.rbegin(); c != cuboids.rend(); c++) {
        fill_occupied_space<MER_LENGTH_GRANULARITY, MER_WIDTH_GRANULARITY>(occupied_space, *c);
        // TODO: check for slight delta_h since last iter, and continue; if so

        std::vector<MaximumEmptyRectangle> mers =
            find_all_maximum_empty_rectangles(occupied_space);

        // TODO: loop through mers and add results to candidates
        for (auto & mer : mers) {
            // TODO: explain
            candidates.emplace_back(mer, c->z + c->height,
                                    pb.height - c->z - c->height);
        }
    }

    return candidates;
}

/** ------------------------------ phase 2 ---------------------------------*/

std::tuple<double, double, double> pick_best_candidate(
                          int length, int width, int height,
                          std::vector<MaximumEmptyCuboid> candidates) {

    // sort the candidates first because filtering is more expensive
    sort(candidates.begin(), candidates.end());

    // find the first candidate that works
    for (auto c = candidates.begin(); c != candidates.end(); c++) {
        // TODO: check if item fits, class method

        // TODO: check if item has stable position, if so use it,
        //  cast things to doubles, and return
    }

    // TODO: remove stub
    if (!candidates.empty())
        return candidates[0].get_stable_position();
    else
        return std::make_tuple(-1.0, -1.0, -1.0);
}

/** ------------------------------ driver ----------------------------------*/

bool process_optimiser_main(const double * const box_position,
                            const double * const box_dimensions, const int tetromino_id,
                            const int tetrominos, double * tetromino_position,
                            double * tetromino_rotation) {

    // TODO: construct box object
    PackingBox test_pb = {0, 0, 0, 1000, 1000, 1000};

    // TODO: construct cuboids from the given information

    // TODO: remove stub
    std::vector<Cuboid> cuboids;
    BoxTetromino bt_test(8, 4, 0, 10, 10, 20, test_pb);
    cuboids.push_back(bt_test);

    // find all candidates
    std::vector<MaximumEmptyCuboid> candidates = find_all_maximum_empty_cuboids(cuboids, test_pb);

    // pick the best one
    std::tuple<int, int, int> sol = pick_best_candidate(10, 5, 8, candidates);

    tetromino_position[0] = double(std::get<0>(sol));
    tetromino_position[1] = double(std::get<1>(sol));
    tetromino_position[2] = double(std::get<2>(sol));

    tetromino_rotation[0] = 1;

    return true;
}
