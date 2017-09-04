#include <stdio.h>
#include <stdlib.h>
#include "cell.h"

Cell Cell_create() {
    Cell cell;

    cell.min = 0;
    cell.max = 0;
    cell.sum = 0;

    return cell;
}

void Cell_destroy(Cell *cell) {
    free(cell);
}

void Cell_print(Cell cell) {
    printf("%lld,%lld,%lld", cell.min, cell.max, cell.sum);
}

void Cell_fill(Cell *cell, int *array, int i, int j) {
    int start = i < j ? i : j;
    int end   = i > j ? i : j;

    cell->min = array[start];
    cell->max = array[start];
    cell->sum = 0;

    int k;
    for(k = start; k <= end; k++) {
        if(cell->min > array[k]) cell->min = array[k];
        if(cell->max < array[k]) cell->max = array[k];
        cell->sum += array[k];
    }
}