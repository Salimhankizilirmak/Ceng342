#include <stdio.h>
#include <numbermake.h>
#include <stdlib.h>

void matrix_vector_multiply(double* matrix, double* vector, double* result, int matrix_size) {
    int i, j;
    for (i = 0; i < matrix_size; i++) {
        result[i] = 0.0;
        for (j = 0; j < matrix_size; j++) {
            result[i] += matrix[i * matrix_size + j] * vector[j];
        }
    }
}

