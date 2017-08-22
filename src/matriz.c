#include <stdio.h>
#include <stdlib.h>
#include "lib/io.h"
#include "lib/matrix.h"

/**
 * @brief      Main function
 *
 *             This is the main function of the project.
 *
 * @return     0
 */
int main(int argc, char *argv[]) {
    FILE *input_file = NULL, *output_file = NULL;

    IOFiles_open(&input_file, &output_file, argc, argv);

    int n, m;
    fscanf(input_file, "%d %d", &n, &m);

    int *array = malloc(sizeof(int) * n), i;
    for(i = 0; i < n; i++) fscanf(input_file, "%d", &array[i]);

    int ***matrix = NULL;

    Matrix_build(&matrix, n);

    Matrix_fill(&matrix, array, n);

    Matrix_print(matrix, n);

    Matrix_destroy(&matrix, n);

    IOFiles_close(input_file, output_file);

    free(array);

    return 0;
}
