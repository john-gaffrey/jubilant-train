#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "matmul_utils.h"

// Function to multiply two matrices A and B and store the result in matrix C
void multiply_matrices(int **A, int **B, int **C, int N) {
    // Initialize the result matrix C to zero
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
        }
    }

    // Matrix multiplication logic
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int N;
    int **A, **B, **C;

    char *endptr;
    struct timespec start_ts, end_ts, diff_ts;

    if (argc < 2) {
        printf("Not enough arguments\n");
        print_usage(argv[0]);
        return -1;
    }

    errno = 0;
    N = strtol(argv[1], &endptr, 10);

    if (errno == ERANGE) {
        printf("N: `%s` caused overflow/underflow, please try another value\n", argv[1]);
        return -1;
    } else if (endptr == argv[1]) {
        printf("N: `%s` has no digits, please try another value\n", argv[1]);
        return -1;
    }

    allocate_matrix(&A, N);
    allocate_matrix(&B, N);
    allocate_matrix(&C, N);

    init_matrix(A, N);
    init_matrix(B, N);

    // run test and take measurements
    clock_gettime(CLOCK_MONOTONIC, &start_ts);
    multiply_matrices(A, B, C, N);
    clock_gettime(CLOCK_MONOTONIC, &end_ts);

    calculate_ts_difference(&start_ts, &end_ts, &diff_ts);

    printf("%d\n", timespec_to_ms(&diff_ts));

    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);

    return 0;
}
