#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "segtree.h"
#include "cell.h"

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

int SegTree_size(int n) {
    double next2PowerExponent = ceil(log2(n));
    double next2Power = pow(2.0, next2PowerExponent);
    return 2 * next2Power - 1;
}

Cell * SegTree_create(int *array, int n) {
    Cell *segtree = malloc(sizeof(Cell) * SegTree_size(n));
    SegTree_construct(segtree, 0, array, 0, n-1);
    return segtree;
}

void SegTree_destroy(Cell *segtree) {
    free(segtree);
}

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

Cell SegTree_query(Cell *segtree, int n, int start, int end) {
    return SegTree_rangeQuery(segtree, 0, start-1, end-1, 0, n-1);
}

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

void SegTree_update(Cell *segtree, int n, int start, int end,
                    int (*transform)(int n)) {
    SegTree_rangeUpdate(segtree, 0, start-1, end-1, 0, n-1, transform);
}