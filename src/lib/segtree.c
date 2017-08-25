#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "segtree.h"
#include "cell.h"

/**
 * @brief      Recursively constructs the Segment Tree
 *
 * @param      segtree  The segtree
 * @param[in]  pos      The current position on the segtree array
 * @param[in]  array    The input array
 * @param[in]  start    The start of the interval
 * @param[in]  end      The end of the interval
 */
void SegTree_construct(Cell *segtree, int pos, int *array, int start, int end) {
    if(start == end) {
        segtree[pos].min = segtree[pos].max = segtree[pos].sum = array[start];

        return;
    }

    int mid = (start + end) / 2;

    SegTree_construct(segtree, 2 * pos + 1, array, start, mid);
    SegTree_construct(segtree, 2 * pos + 2, array, mid + 1, end);

    Cell left = segtree[2 * pos + 1];
    Cell right = segtree[2 * pos + 2];

    segtree[pos].min = left.min < right.min ? left.min : right.min;
    segtree[pos].max = left.max > right.max ? left.max : right.max;
    segtree[pos].sum = left.sum + right.sum;
}

/**
 * @brief      Calculates the Segment Tree array size given the input array size
 *
 * @param[in]  n     The input array size
 *
 * @return     The size of the Segment Tree array
 */
int SegTree_size(int n) {
    double nextPower = ceil(log2 (n));
    return 2 * pow(2.0, nextPower) - 1;
}

/**
 * @brief      Creates a new Segment Tree
 *
 * @param[in]  array  The input array
 * @param[in]  n      The input array length
 *
 * @return     A pointer to the created Segment Tree
 */
Cell * SegTree_create(int *array, int n) {
    Cell *segtree = malloc(sizeof(Cell) * SegTree_size(n));
    SegTree_construct(segtree, 0, array, 0, n-1);
    return segtree;
}

/**
 * @brief      Destroys the given Segment Tree
 *
 * @param      segtree  The segtree
 */
void SegTree_destroy(Cell *segtree) {
    free(segtree);
}