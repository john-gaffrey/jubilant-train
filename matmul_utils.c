#include "matmul_utils.h"

#define MAX_MATRIX_VAL 1000

// calculates the difference between a start and end time
void calculate_ts_difference(struct timespec *start_ts,
                             struct timespec *end_ts,
                             struct timespec *diff_ts) {
    diff_ts->tv_sec = end_ts->tv_sec - start_ts->tv_sec;
    diff_ts->tv_nsec = end_ts->tv_nsec - start_ts->tv_nsec;
    if (end_ts->tv_nsec < start_ts->tv_nsec)
    {
        diff_ts->tv_sec -= 1;
        diff_ts->tv_nsec += 1000000000L;
    }
}

// returns the timespec time in milliseconds
int timespec_to_ms(struct timespec *ts) {
    return ts->tv_sec * 1000L + ts->tv_nsec/1000000;
}

void allocate_matrix(int ***matrix, int N) {
    *matrix = malloc(N * sizeof(int *));

    for (int i = 0; i < N; i++) {
        (*matrix)[i] = malloc(N * sizeof(int));
    }
}

void init_matrix(int **matrix, int N) {
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % MAX_MATRIX_VAL;
        }
    }
}

void free_matrix(int **matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

void print_usage(char* prog_name) {
    printf("Usage:\n");
    printf("%s N [LOG]\n", prog_name);
    printf("N: required - the size of square matrices to multiply\n");
    printf("LOG: optional, specifies the log file to write the matrix details to. \
            Defaults to %s.log\n", prog_name);
}

void print_matrix(int **matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}
