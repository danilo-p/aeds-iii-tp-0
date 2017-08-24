#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/io.h"
#include "lib/matrix.h"

/**
 * @brief      Main function
 *
 *             This is the main function of the project.
 *
 * @return     0
 */
int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *array = malloc(sizeof(int) * n), i;
    for(i = 0; i < n; i++) scanf("%d", &array[i]);

    Cell **matrix = Matrix_create(n);

    Matrix_fill(&matrix, array, n);

    Matrix_print(matrix, n);

    // char cmd[4];
    // int a, b, j;

    // for(i = 0; i < m; i++) {
    //     scanf("%s %d %d", cmd, &a, &b);

    //     // BUG with the output values

    //     if(strcmp(cmd, "Add") == 0) {
    //         for(j = a - 1; j < b; j++) array[j]++;
    //         Matrix_fill(&matrix, array, n);
    //     } else if(strcmp(cmd, "Sub") == 0) {
    //         for(j = a - 1; j < b; j++) array[j]--;
    //         Matrix_fill(&matrix, array, n);
    //     } else if(strcmp(cmd, "Min") == 0) {
    //         printf("%d\n", matrix[a-1][b-1][0]);
    //     } else if(strcmp(cmd, "Max") == 0) {
    //         printf("%d\n", matrix[a-1][b-1][1]);
    //     } else if(strcmp(cmd, "Sum") == 0) {
    //         printf("%d\n", matrix[a-1][b-1][2]);
    //     }
    // }

    Matrix_destroy(&matrix, n);

    free(array);

    return 0;
}
