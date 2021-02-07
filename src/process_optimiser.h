#ifndef PROCESS_OPTIMISER_HEADER
#define PROCESS_OPTIMISER_HEADER

bool process_optimiser_main(const double * const box_position,
        const double * const box_dimensions, const int tetromino_id,
        const int tetrominos, double * tetromino_position,
        double * tetromino_rotation);


#endif
