#include "cell.h"

#ifndef MATRIX_H
#define MATRIX_H


/**
 * @brief      Builds the matrix with the given array
 *
 *             Complexity: O(n²)
 *
 * @param[in]  n     The length of the input array
 *
 * @return     A pointer to the created matrix
 */
Cell ** Matrix_create(int n);

/**
 * @brief      Fills the matrix with the given data
 *
 *             Complexity: O(n³), because the maximum interval given to
 *             Cell_Fill has size n, and is executed n² times.
 *
 * @param      matrix  The matrix
 * @param      array   The array
 * @param[in]  n       The length of the input array
 */
void Matrix_fill(Cell **matrix, int *array, int n);

/**
 * @brief      Destroys the matrix
 *
 *             Complexity: O(n)
 *
 * @param      matrix  The matrix
 * @param[in]  n       The length of the input array
 */
void Matrix_destroy(Cell **matrix, int n);

/**
 * @brief      Prints the matrix
 *
 *             Complexity: O(n²)
 *
 * @param      matrix  The matrix
 * @param[in]  n       The length of the input array
 */
void Matrix_print(Cell **matrix, int n);

#endif