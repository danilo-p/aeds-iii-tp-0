#ifndef CELL_H
#define CELL_H

/**
 * @brief      Cell structure
 *
 *             This struct stores the max, min and the sum of the interval. Also
 *             stores the i and j indexes.
 */
 struct cell {
    /** The interval i to j on the array */
    int i, j;
    /** Minimum and Maximum value of the interval */
    int min, max;
    /** Sum of the interval */
    int sum;
};

typedef struct cell Cell;

Cell Cell_create();

void Cell_destroy(Cell *cell);

void Cell_print(Cell cell);

#endif