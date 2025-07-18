#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matmul_utils.h"
#define N 768         // Size of the square matrix
#define BLOCK_SIZE 64 // Size of the block, tuned for cache

void multiplyBlocked(int A[N][N], int B[N][N], int C[N][N]) {
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

// Utility to initialize a matrix with random values
void initMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mat[i][j] = rand() % 10;
}

int main(int argc, char* argv[]) {
    int A[N][N], B[N][N], C[N][N];
    struct timespec start_ts, end_ts, diff_ts;

    initMatrix(A);
    initMatrix(B);

    clock_gettime(CLOCK_MONOTONIC, &start_ts);
    multiplyBlocked(A, B, C);
    clock_gettime(CLOCK_MONOTONIC, &end_ts);

    // diff
    diff_ts.tv_sec = end_ts.tv_sec - start_ts.tv_sec;
    diff_ts.tv_nsec = end_ts.tv_nsec - start_ts.tv_nsec;
    if (end_ts.tv_nsec < start_ts.tv_nsec)
    {
        diff_ts.tv_sec -= 1;
        diff_ts.tv_nsec += 1000000000L;
    }

    // print runtime in ms
    printf("%ld\n", diff_ts.tv_sec * 1000L + diff_ts.tv_nsec/1000000);

    return 0;
}
