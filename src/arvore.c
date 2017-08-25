#include <stdio.h>
#include <stdlib.h>
#include "lib/segtree.h"

/**
 * @brief      Main function
 *
 *             This is the main function of the project.
 *
 * @return     0
 */
int main() {
    /*----------  Initialization  ----------*/

    int n, m;
    scanf("%d %d", &n, &m);

    int *array = malloc(sizeof(int) * n), i;
    for(i = 0; i < n; i++) scanf("%d", &array[i]);

    Cell *segtree = SegTree_create(array, n);

    /*----------  Finalization  ----------*/

    SegTree_destroy(segtree);

    free(array);

    return 0;
}
