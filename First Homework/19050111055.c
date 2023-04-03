//Salimhan KIZILIRMAK 19050111055
//An introduction to the mpi library and parallel programming. We measured the durations by increasing the number of threads with mpi.
#include <numbermake.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define LARGE_MATRIX_SIZE (rank % 10000)
#define SMALL_MATRIX_SIZE (100 + (rank % 100))



int main(int argc, char** argv) {
    int rank, size;
    int i, j;
    double start_time, end_time;
    double* large_matrix;
    double* small_matrix;
    double* vector;
    double* result;
    int matrix_size;

    MPI_Init(&argc, &argv);//MPI_Init initializes the MPI environment. MPI_Comm_rank gets the rank of the current process, and MPI_Comm_size gets the total number of processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    matrix_size = LARGE_MATRIX_SIZE;
    if (rank == 0) {
        large_matrix = (double*) malloc(matrix_size * matrix_size * sizeof(double));
        vector = (double*) malloc(matrix_size * sizeof(double));
        result = (double*) malloc(matrix_size * sizeof(double));
        for (i = 0; i < matrix_size; i++) {
            vector[i] = i;
            for (j = 0; j < matrix_size; j++) {
                large_matrix[i * matrix_size + j] = (double)rand() / (double)RAND_MAX;
            }
        }
    }

    MPI_Bcast(&matrix_size, 1, MPI_INT, 0, MPI_COMM_WORLD);//MPI_Bcast broadcasts the value of matrix_size from process 0 to all other processes. If the current process has a rank other than 0, vector and result are initialized.
    if (rank != 0) {
        vector = (double*) malloc(matrix_size * sizeof(double));
        result = (double*) malloc(matrix_size * sizeof(double));
    }

    small_matrix = (double*) malloc(SMALL_MATRIX_SIZE * SMALL_MATRIX_SIZE * sizeof(double));
    for (i = 0; i < SMALL_MATRIX_SIZE; i++) {
        for (j = 0; j < SMALL_MATRIX_SIZE; j++) {
            small_matrix[i * SMALL_MATRIX_SIZE + j] = (double)rand() / (double)RAND_MAX;
        }
    }

    start_time = MPI_Wtime();
    MPI_Bcast(vector, matrix_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (i = rank; i < matrix_size; i += size) {
        matrix_vector_multiply(&large_matrix[i * matrix_size], small_matrix, &result[i], matrix_size);
    }

    MPI_Reduce(result, vector, matrix_size, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Elapsed time is %lf seconds for parallel mxv with %d processes\n", end_time - start_time, size);
    }

    free(small_matrix);
    if (rank == 0) {
        free(large_matrix);
        free(vector);
        free(result);
    } else {
        free(vector);
        free(result);
    }

    MPI_Finalize();

    return 0;
}

