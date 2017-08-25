#include "cell.h"

#ifndef SEGTREE_H
#define SEGTREE_H

Cell * SegTree_create(int *array, int n);

void SegTree_destroy(Cell *segtree);

#endif