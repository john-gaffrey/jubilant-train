#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "matmul_utils.h"

#define BLOCK_SIZE 64 // Size of the block, tuned for cache

void multiply_in_blocks(int **A, int **B, int **C, int N) {
    // Initialize result matrix C to zero
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = 0;

    // Loop tiling / blocking for better cache usage
    for (int ii = 0; ii < N; ii += BLOCK_SIZE) {
        for (int jj = 0; jj < N; jj += BLOCK_SIZE) {
            for (int kk = 0; kk < N; kk += BLOCK_SIZE) {

                // Multiply sub-blocks
                for (int i = ii; i < ii + BLOCK_SIZE && i < N; i++) {
                    for (int j = jj; j < jj + BLOCK_SIZE && j < N; j++) {
                        int sum = C[i][j]; // Load once
                        for (int k = kk; k < kk + BLOCK_SIZE && k < N; k++) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] = sum; // Store once
                    }
                }

            }
        }
    }
}

int main(int argc, char* argv[]) {
    int N;
    int **a, **b, **c;

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

    allocate_matrix(&a, N);
    allocate_matrix(&b, N);
    allocate_matrix(&c, N);

    init_matrix(a, N);
    init_matrix(b, N);

    // run test and take measurements
    clock_gettime(CLOCK_MONOTONIC, &start_ts);
    multiply_in_blocks(a, b, c, N);
    clock_gettime(CLOCK_MONOTONIC, &end_ts);

    calculate_ts_difference(&start_ts, &end_ts, &diff_ts);

    printf("%d\n", timespec_to_ms(&diff_ts));

    free_matrix(a, N);
    free_matrix(b, N);
    free_matrix(c, N);

    return 0;
}
