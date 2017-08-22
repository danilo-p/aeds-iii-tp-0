#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "util.h"

/**
 * @brief      Builds the 3D matrix with the given array
 *
 * @param      matrix  The matrix
 * @param[in]  n       The length of the input array
 */
void Matrix_build(int ****matrix, int n) {
    int i, j;

    *matrix = malloc(sizeof(int **) * n);
    if(*matrix == NULL) exit_with_code("Could not alloc memory for matrix", -1);

    for(i = 0; i < n; i++) {
        (*matrix)[i] = malloc(sizeof(int *) * n);
        if((*matrix)[i] == NULL) exit_with_code("Could not alloc memory for matrix", -1);

        for(j = 0; j < n; j++) {
            (*matrix)[i][j] = malloc(sizeof(int) * 3);
            if((*matrix)[i][j] == NULL) exit_with_code("Could not alloc memory for matrix", -1);
        }
    }
}

/**
 * @brief      Fills the 3D matrix with the given data
 *
 * @param      matrix  The matrix
 * @param      array   The array
 * @param[in]  n       The length of the input array
 */
void Matrix_fill(int ****matrix, int *array, int n) {
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

            (*matrix)[i][j][0] = min;
            (*matrix)[i][j][1] = max;
            (*matrix)[i][j][2] = sum;
        }
    }
}

/**
 * @brief      Destroys the 3D Matrix
 *
 * @param      matrix  The matrix
 * @param[in]  n       The length of the input array
 */
void Matrix_destroy(int ****matrix, int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) free((*matrix)[i][j]);
        free((*matrix)[i]);
    }
    free(*matrix);
}

/**
 * @brief      Prints the 3D Matrix
 *
 * @param      matrix  The matrix
 * @param[in]  n       The length of the input array
 */
void Matrix_print(int ***matrix, int n) {
    int i, j, k;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            for(k = 0; k < 3; k++) printf("%d ", matrix[i][j][k]);
            printf("\t");
        }
        printf("\n");
    }
}