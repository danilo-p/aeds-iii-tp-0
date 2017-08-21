#include <stdio.h>
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

    if(IOFilesOpen(&input_file, &output_file, argc, argv) < 0) return -1;

    int n, m;
    fscanf(input_file, "%d %d", &n, &m);

    printf("%d %d\n", n, m);

    // BUG while reading negative numbers
    int array[n], i;
    for(i = 0; i < n; i++) fscanf(input_file, "%d", &array[i]);

    for(i = 0; i < n; i++) printf("%d ", array[i]);
    printf("\n");

    IOFilesClose(input_file, output_file);

    return 0;
}
