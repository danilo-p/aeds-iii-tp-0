#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/segtree.h"
#include "lib/cell.h"

int add(int a) { return a+1; }

int sub(int a) { return a-1; }

/**
 * @brief      Main function
 *
 *             This function uses the Bryan solution based on a Segment Tree
 *             that stores the input array data.
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

    /*----------  Manipulation of the segtree  ----------*/

    char cmd[4];
    int a, b;

    for(i = 0; i < m; i++) {
        scanf("%s %d %d", cmd, &a, &b);

        if(strcmp(cmd, "Add") == 0) {
            SegTree_update(segtree, n, a, b, add);
        } else if(strcmp(cmd, "Sub") == 0) {
            SegTree_update(segtree, n, a, b, sub);
        } else if(strcmp(cmd, "Min") == 0) {
            printf("%lld\n", (SegTree_query(segtree, n, a, b)).min);
        } else if(strcmp(cmd, "Max") == 0) {
            printf("%lld\n", (SegTree_query(segtree, n, a, b)).max);
        } else if(strcmp(cmd, "Sum") == 0) {
            printf("%lld\n", (SegTree_query(segtree, n, a, b)).sum);
        }
    }

    /*----------  Finalization  ----------*/

    SegTree_destroy(segtree);

    free(array);

    return 0;
}
