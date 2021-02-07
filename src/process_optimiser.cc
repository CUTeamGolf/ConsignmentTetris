#include "process_optimiser.h"

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
