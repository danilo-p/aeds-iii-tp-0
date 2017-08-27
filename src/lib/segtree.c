#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "segtree.h"
#include "cell.h"

/**
 * @brief      Recursively constructs the Segment Tree
 *
 *             Complexity:
 *
 *             With n being the Segment Tree's number of nodes, the complexity
 *             is O(n), because we need to visit every node of the tree to
 *             calculate its data.
 *
 * @param      segtree  The Segment Tree array
 * @param[in]  pos      The current position on the segtree
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
 * @brief      Calculates the Segment Tree's number of nodes with the given the
 *             input array size
 *
 *             The number of nodes n required for a segtree is calculated with
 *             the length of the input array. In the best case, the length L is
 *             a power of 2, so the number of nodes is n=2·L-1. If L is not a
 *             power of 2, we have to find the next power of 2 after L. In this
 *             case, the number of nodes will not pass from n=2·2^((log L) + 1) -
 *             1, which can be simplified to n=4·L-1.
 *
 *             Being n the input array length, let np the power of 2 that is
 *             equal or higher than n. The size of the Segment Tree array will
 *             be 2·np-1.
 *
 *             The strategy adopted here is to calculate the log2 of n and get
 *             the ceil of the result. This way, we can power 2 for the result
 *             and get the next power of 2. Then, we use 2·(2^np)-1 to get the
 *             the size of the Segment Tree array.
 *
 *             Complexity: (1)
 *
 * @param[in]  n     The input array size
 *
 * @return     The size of the Segment Tree array
 */
int SegTree_size(int n) {
    double next2PowerExponent = ceil(log2(n));
    double next2Power = pow(2.0, next2PowerExponent);
    return 2 * next2Power - 1;
}

/**
 * @brief      Creates a new Segment Tree
 *
 *             Complexity:
 *
 *             The complexity for creating a new Segment Tree is related to the
 *             function SegTree_construct, which is O(N), being N the number of
 *             nodes of the tree.
 *
 *             The number of nodes N, in the best case is 2·n-1, with n being
 *             the input array length. In worst case N will not pass from 4·n-1.
 *             The full explanation for this is on the SegTree_size function
 *             description.
 *
 *             In all cases, the complexity for creating a new Segment Tree is
 *             O(n).
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
 *             Complexity: O(1)
 *
 * @param      segtree  The segtree
 */
void SegTree_destroy(Cell *segtree) {
    free(segtree);
}

/**
 * @brief      Perform a range query on the Segment Tree recursivelly
 *
 *             Complexity:
 *
 *             In the best case, the range of the query will be from 0 to (L -
 *             1), being L the length of the input array. In this case, the
 *             complexity for retrieving data from the segtree is O(1).
 *
 *             In the worst case, the range of the query will have length of 1
 *             (query of 1 element). In this case, the alghoritm will dive into
 *             the tree til reach the correspondant leaf. The complexity for
 *             retrieving the leaf data will be of O(H), with H begin the height
 *             of the tree.
 *
 *             As the Segment Tree is a Full Binary Tree, the height of the tree
 *             will correspond log N, being N the number of nodes. So the
 *             complexity for retrieving data from a leaf is O(log N).
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
 *             Complexity: The complexity here is related to the complexity of
 *             the SegTree_rangeQuery function, which is O(log N), being N the
 *             number of nodes of the tree.
 *
 *             The number of nodes N, in the best case is 2·n-1, with n being
 *             the input array length. In worst case N will not pass from 4·n-1.
 *             The full explanation for this is on the SegTree_size function
 *             description.
 *
 *             With 2·n-1 or 4·n-1, the complexity of the function is O(log n).
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
 * @brief      Recursively updates the Segment Tree
 *
 *             Complexity:
 *
 *             As the updates are realized on the leafs of the tree, and then
 *             the nodes that represent the intervals have to be updated, the
 *             cost on the update will be related to the amount of nodes that
 *             has to be updated plus the height of the tree. The cost to reach
 *             a leaf is log H, being H the height of the tree. Let LF the
 *             number of leafs to be updated, that is the same as the size of
 *             the interval to be updated (end-start-1).
 *
 *             As the Segment Tree is a Full Binary Tree, the height of the tree
 *             will correspond log N, being N the number of nodes. So the
 *             complexity for retrieving data from a leaf is O(log N).
 *
 *             The complexity of a update is O(LF·log N).
 *
 * @param      segtree    The segtree
 * @param[in]  pos        The current position on the segtree array
 * @param[in]  start      The start of the interval (0-indexed, inclusive)
 * @param[in]  end        The end of the interval (0-indexed, inclusive)
 * @param[in]  currStart  The current start of the interval (0-indexed,
 *                        inclusive)
 * @param[in]  currEnd    The current end of the interval (0-indexed, inclusive)
 * @param[in]  transform  The function that will transform the leafs data.
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
 *             Complexity: The complexity here is related to the complexity of
 *             the SegTree_rangeUpdate function, which is O(LF·log N), being N
 *             the number of nodes of the tree, and LF is end - start - 1.
 *
 *             The number of nodes N, in the best case is 2·n-1, with n being
 *             the input array length. In worst case N will not pass from 4·n-1.
 *             The full explanation for this is on the SegTree_size function
 *             description.
 *
 *             With 2·n-1 or 4·n-1, the complexity of the function is O(LF·log
 *             n).
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