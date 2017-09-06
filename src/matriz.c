#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/matrix.h"
#include "lib/cell.h"

/**
 * @brief      Main function
 *
 *             This function uses the Nubby solution based on a matrix that
 *             stores the data for each possible interval.
 *
 *             Complexity: O(n³)
 *
 * @return     0
 */
int main() {
    /*----------  Initialization  ----------*/

    int n, m;
    scanf("%d %d", &n, &m);

    int *array = malloc(sizeof(int) * n), i;
    for(i = 0; i < n; i++) scanf("%d", &array[i]);

    Cell **matrix = Matrix_create(n);

    Matrix_fill(matrix, array, n);

    /*----------  Manipulation of the matrix  ----------*/

    char cmd[4];
    int a, b, j;

    for(i = 0; i < m; i++) {
        scanf("%s %d %d", cmd, &a, &b);

        if(strcmp(cmd, "Add") == 0) {
            for(j = a - 1; j < b; j++) array[j]++;
            Matrix_fill(matrix, array, n);
        } else if(strcmp(cmd, "Sub") == 0) {
            for(j = a - 1; j < b; j++) array[j]--;
            Matrix_fill(matrix, array, n);
        } else if(strcmp(cmd, "Min") == 0) {
            printf("%lld\n", matrix[a-1][b-1].min);
        } else if(strcmp(cmd, "Max") == 0) {
            printf("%lld\n", matrix[a-1][b-1].max);
        } else if(strcmp(cmd, "Sum") == 0) {
            printf("%lld\n", matrix[a-1][b-1].sum);
        }
    }

    /*----------  Finalization  ----------*/

    Matrix_destroy(matrix, n);

    free(array);

    return 0;
}
