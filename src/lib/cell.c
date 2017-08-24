#include <stdio.h>
#include <stdlib.h>
#include "cell.h"

/**
 * @brief      Creates a new cell and initialize it's values with 0
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
 * @param[in]  cell  The cell
 */
void Cell_print(Cell cell) {
    printf("%d,%d,%d", cell.min, cell.max, cell.sum);
}