#include <stdio.h>
#include <numbermake.h>

void multiplication(double **matrix, double *vector, int n, int m, double *result) {
  
for (int i = 0; i < n; i++) {
        result[i] = 0.0;
        for (int j = 0; j < m; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return;
}

