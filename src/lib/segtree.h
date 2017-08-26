#include "cell.h"

#ifndef SEGTREE_H
#define SEGTREE_H

Cell * SegTree_create(int *array, int n);

Cell SegTree_query(Cell *segtree, int start, int end);

void SegTree_destroy(Cell *segtree);

#endif