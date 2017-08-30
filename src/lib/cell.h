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

/**
 * @brief      Creates a new cell and initialize it's values with 0
 *
 *             Complexity: O(1)
 *
 * @return     The created cell
 */
Cell Cell_create();

/**
 * @brief      Destroys the given cell
 *
 *             Complexity: O(1)
 *
 * @param      cell  The cell to be destroyed
 */
void Cell_destroy(Cell *cell);

/**
 * @brief      Prints the content of the given cell.
 *
 *             It doesn't print a new line.
 *
 *             Complexity: O(1)
 *
 * @param[in]  cell  The cell
 */
void Cell_print(Cell cell);

/**
 * @brief      Fill the cell data with the given array and intervals
 *
 *             Complexity: O(size-end)
 *
 * @param      cell   The cell
 * @param      array  The array
 * @param[in]  i      Start of the interval
 * @param[in]  j      End of the interval
 */
void Cell_fill(Cell *cell, int *array, int i, int j);

#endif
