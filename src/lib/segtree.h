#include "cell.h"

#ifndef SEGTREE_H
#define SEGTREE_H

Cell * SegTree_create(int *array, int n);

Cell SegTree_query(Cell *segtree, int n, int start, int end);

void SegTree_destroy(Cell *segtree);

void SegTree_update(Cell *segtree, int n, int start, int end, int (*transform)(int n));

#endif