#include <numbermake.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
 

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    char *output_file = argv[3];

    double **matrix = (double **) malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double *) calloc(cols, sizeof(double));
    }
    double *result = (double *) malloc(rows * sizeof(double));
    double *vector = (double *) malloc(cols * sizeof(double));

    
    srand((unsigned short)19050111055);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = ((double) rand() / RAND_MAX) * 99.0 + 1.0;
        }
    }

    // Create random vector
    for (int i = 0; i < cols; i++) {
        vector[i] = ((double) rand() / RAND_MAX) * 99.0 + 1.0;
    }

 
    multiplication(matrix, vector, rows, cols, result);


    FILE *fp;
    fp = fopen(output_file, "w");
    for (int i = 0; i < rows; i++) {
        fprintf(fp, "%.2f\n", result[i]);
    }
    fclose(fp);


    
   if (argc != 4) {
        printf("Usage: ./matrix-vector <n> <m> <output_file>\n");
        return 1;
    }
	for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    free(result);

    return 0;
}