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
 * @param[in]  start    The start of the interval (0-indexed, inclusive)
 * @param[in]  end      The end of the interval (0-indexed, inclusive)
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
 * @param[in]  pos        The position
 * @param[in]  start      The start of the interval (0-indexed, inclusive)
 * @param[in]  end        The end of the interval (0-indexed, inclusive)
 * @param[in]  currStart  The current start of the interval (0-indexed,
 *                        inclusive)
 * @param[in]  currEnd    The current end of the interval (0-indexed, inclusive)
 *
 * @return     The results of the query
 */
Cell SegTree_rangeQuery(Cell *segtree, int pos, int start, int end,
                        int currStart, int currEnd) {
    if(start <= currStart && end >= currEnd) // Total interval overlap
        return segtree[pos];
    else if(start > currEnd || end < currStart) // No interval overlap
        return (Cell) {
            .min = INT_MAX,
            .max = INT_MIN,
            .sum = 0
        };

    // Partial interval overlap
    int mid = (currStart + currEnd) / 2;
    Cell left = SegTree_rangeQuery(segtree, 2 * pos + 1, start, end, currStart, mid);
    Cell right = SegTree_rangeQuery(segtree, 2 * pos + 2, start, end, mid + 1, currEnd);

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
 * @param[in]  n        The input array length
 * @param[in]  start    The start of the interval (1-indexed, inclusive)
 * @param[in]  end      The end of the interval (1-indexed, inclusive)
 *
 * @return     The results of the query
 */
Cell SegTree_query(Cell *segtree, int n, int start, int end) {
    return SegTree_rangeQuery(segtree, 0, start-1, end-1, 0, n-1);
}

/**
 * @brief      Recursively constructs the Segment Tree
 *
 * @param      segtree    The segtree
 * @param[in]  pos        The current position on the segtree array
 * @param[in]  start      The start of the interval (0-indexed, inclusive)
 * @param[in]  end        The end of the interval (0-indexed, inclusive)
 * @param[in]  transform  The transform function
 */
void SegTree_rangeUpdate(Cell *segtree, int pos, int start, int end,
                    int currStart, int currEnd,
                    int (*transform)(int n)) {
    // No overlap
    if(start > currEnd || end < currStart) return;

    if(currStart == currEnd) {
        segtree[pos].min = segtree[pos].max = segtree[pos].sum = transform(segtree[pos].min);
        return;
    }

    int mid = (currStart + currEnd) / 2;
    SegTree_rangeUpdate(segtree, 2 * pos + 1, start, end, currStart, mid, transform);
    SegTree_rangeUpdate(segtree, 2 * pos + 2, start, end, mid+1, currEnd, transform);

    Cell left = segtree[2 * pos + 1];
    Cell right = segtree[2 * pos + 2];

    segtree[pos].min = left.min < right.min ? left.min : right.min;
    segtree[pos].max = left.max > right.max ? left.max : right.max;
    segtree[pos].sum = left.sum + right.sum;
}

/**
 * @brief      Interface for the recursive segtree update
 *
 * @param      segtree    The segtree
 * @param[in]  n          The length of the input array
 * @param[in]  start      The start of the interval (1-indexed, inclusive)
 * @param[in]  end        The end of the interval (1-indexed, inclusive)
 * @param[in]  transform  The transform function
 */
void SegTree_update(Cell *segtree, int n, int start, int end, int (*transform)(int n)) {
    SegTree_rangeUpdate(segtree, 0, start-1, end-1, 0, n-1, transform);
}