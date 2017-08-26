#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "segtree.h"
#include "cell.h"

/**
 * @brief      Recursively constructs the Segment Tree
 *
 * @param      segtree  The segtree
 * @param[in]  pos      The current position on the segtree array
 * @param[in]  array    The input array
 * @param[in]  start    The start of the interval (inclusive)
 * @param[in]  end      The end of the interval (inclusive)
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
    double nextPower = ceil(log2(n));
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

/**
 * @brief      Perform a range query on the segment tree recursivelly
 *
 * @param      segtree    The segtree
 * @param[in]  start      The start of the interval (inclusive)
 * @param[in]  end        The end of the interval (inclusive)
 * @param[in]  currStart  The current start of the interval (inclusive)
 * @param[in]  currEnd    The current end of the interval (inclusive)
 * @param[in]  pos        The position
 *
 * @return     The results of the query
 */
Cell SegTree_rangeQuery(Cell *segtree, int start, int end,
                    int currStart, int currEnd, int pos) {
    if(start <= currStart && currEnd <= end)
        return segtree[pos];
    else if(start > currEnd || end < currStart)
        return (Cell) {
            .min = INT_MAX,
            .max = INT_MIN,
            .sum = 0
        };

    int mid = (currStart + currEnd) / 2;
    Cell left = SegTree_rangeQuery(segtree, start, end, currStart, mid, 2 * pos + 1);
    Cell right = SegTree_rangeQuery(segtree, start, end, mid + 1, currEnd, 2 * pos + 1);

    return (Cell) {
        .min = left.min < right.min ? left.min : right.min,
        .max = left.max > right.max ? left.max : right.max,
        .sum = left.sum + right.sum
    };
}

/**
 * @brief      Interface for the recursive range query
 *
 * @param      segtree  The segtree
 * @param[in]  start    The start of the interval (inclusive)
 * @param[in]  end      The end of the interval (exclusive)
 *
 * @return     The results of the query
 */
Cell SegTree_query(Cell *segtree, int start, int end) {
    return SegTree_rangeQuery(segtree, start, end-1, start, end-1, 0);
}
