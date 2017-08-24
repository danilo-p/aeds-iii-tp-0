#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include "matrix.h"
#include "util.h"

/**
 * @brief      Builds the matrix with the given array
 *
 * @param[in]  n     The length of the input array
 *
 * @return     A pointer to the created matrix
 */
Cell ** Matrix_create(int n) {
    Cell **matrix = malloc(sizeof(Cell *) * n);

    if(matrix == NULL) exit_with_code("Could not allocate memory for matrix", -1);

    int i, j;
    for(i = 0; i < n; i++) {
        matrix[i] = malloc(sizeof(Cell) * n);

        if(matrix[i] == NULL) exit_with_code("Could not allocate memory for matrix", -1);

        for(j = 0; j < n; j++) matrix[i][j] = Cell_create();
    }

    return matrix;
}

/**
 * @brief      Fills the matrix with the given data
 *
 * @param      matrix  The matrix
 * @param      array   The array
 * @param[in]  n       The length of the input array
 */
void Matrix_fill(Cell **matrix, int *array, int n) {
    int i, j, k;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            matrix[i][j].i = i;
            matrix[i][j].j = j;

            int start = i < j ? i : j;
            int end   = i > j ? i : j;

            matrix[i][j].min = array[start];
            matrix[i][j].max = array[start];
            matrix[i][j].sum = 0;

            for(k = start; k <= end; k++) {
                if(matrix[i][j].min > array[k]) matrix[i][j].min = array[k];
                if(matrix[i][j].max < array[k]) matrix[i][j].max = array[k];
                matrix[i][j].sum += array[k];
            }
        }
    }
}

/**
 * @brief      Destroys the matrix
 *
 * @param      matrix  The matrix
 * @param[in]  n       The length of the input array
 */
void Matrix_destroy(Cell ***matrix, int n) {
    int i;
    for(i = 0; i < n; i++) free((*matrix)[i]);
    free(*matrix);
}

/**
 * @brief      Prints the matrix
 *
 * @param      matrix  The matrix
 * @param[in]  n       The length of the input array
 */
void Matrix_print(Cell **matrix, int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            Cell_print(matrix[i][j]);
            printf("\t");
        }
        printf("\n");
    }
}