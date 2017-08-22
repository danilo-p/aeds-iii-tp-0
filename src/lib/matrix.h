#ifndef MATRIX_H
#define MATRIX_H

void Matrix_build(int ****matrix, int n);

void Matrix_fill(int ****matrix, int *array, int n);

void Matrix_destroy(int ****matrix, int n);

void Matrix_print(int ***matrix, int n);

#endif