#include <stdio.h>
#include <stdlib.h>
#include "cell.h"

/**
 * @brief      Creates a new cell and initialize it's values with 0
 *
 *             Complexity: O(1)
 *
 * @return     The created cell
 */
Cell Cell_create() {
    Cell cell;

    cell.i = 0;
    cell.j = 0;
    cell.min = 0;
    cell.max = 0;
    cell.sum = 0;

    return cell;
}

/**
 * @brief      Destroys the given cell
 *
 *             Complexity: O(1)
 *
 * @param      cell  The cell to be destroyed
 */
void Cell_destroy(Cell *cell) {
    free(cell);
}

/**
 * @brief      Prints the content of the given cell.
 *
 *             It doesn't print a new line.
 *
 *             Complexity: O(1)
 *
 * @param[in]  cell  The cell
 */
void Cell_print(Cell cell) {
    printf("%d,%d,%d", cell.min, cell.max, cell.sum);
}

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
void Cell_fill(Cell *cell, int *array, int i, int j) {
    cell->i = i;
    cell->j = j;

    int start = i < j ? i : j;
    int end   = i > j ? i : j;

    cell->min = array[start];
    cell->max = array[start];
    cell->sum = 0;

    int k;
    for(k = start; k <= end; k++) {
        if(cell->min > array[k]) cell->min = array[k];
        if(cell->max < array[k]) cell->max = array[k];
        cell->sum += array[k];
    }
}