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
void Matrix_fill(Cell ***matrix, int *array, int n) {
    int i, j, k;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            int min = array[i];
            int max = array[i];
            int sum = array[i];

            for(k = i+1; k < j; k++) {
                if(min > array[k]) min = array[k];
                if(max < array[k]) max = array[k];
                sum += array[k];
            }

            (*matrix)[i][j].min = min;
            (*matrix)[i][j].max = max;
            (*matrix)[i][j].sum = sum;
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