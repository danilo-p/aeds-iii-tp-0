#include <stdio.h>
#include <stdlib.h>
#include "lib/io.h"

/**
 * @brief      Main function
 *
 *             This is the main function of the project.
 *
 * @return     0
 */
int main(int argc, char *argv[]) {
    FILE *input_file = NULL, *output_file = NULL;

    if(IOFiles_open(&input_file, &output_file, argc, argv) < 0) return -1;

    int n, m;
    fscanf(input_file, "%d %d", &n, &m);

    int *array = malloc(sizeof(int) * n), i;
    for(i = 0; i < n; i++) fscanf(input_file, "%d", &array[i]);

    int ***matrix = malloc(sizeof(int **) * n), j, k;
    for(i = 0; i < n; i++) {
        matrix[i] = malloc(sizeof(int *) * n);
        for(j = 0; j < n; j++) {
            matrix[i][j] = malloc(sizeof(int) * 3);
            int min = array[i];
            int max = array[i];
            int sum = array[i];

            for(k = i+1; k < j; k++) {
                if(min > array[k]) min = array[k];
                if(max < array[k]) max = array[k];
                sum += array[k];
            }

            matrix[i][j][0] = min;
            matrix[i][j][1] = max;
            matrix[i][j][2] = sum;
        }
    }

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            for(k = 0; k < 3; k++) printf("%d ", matrix[i][j][k]);
            printf("\t");
        }
        printf("\n");
    }

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) free(matrix[i][j]);
        free(matrix[i]);
    }
    free(matrix);

    IOFiles_close(input_file, output_file);

    free(array);

    return 0;
}
