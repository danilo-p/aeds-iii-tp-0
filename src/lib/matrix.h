#include "cell.h"

#ifndef MATRIX_H
#define MATRIX_H

Cell ** Matrix_create(int n);

void Matrix_fill(Cell **matrix, int *array, int n);

void Matrix_destroy(Cell **matrix, int n);

void Matrix_print(Cell **matrix, int n);

#endif