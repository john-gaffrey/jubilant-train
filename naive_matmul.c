#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 768  // Size of the square matrices

void initMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mat[i][j] = rand() % 10;
}

// Function to multiply two matrices A and B and store the result in matrix C
void multiplyMatrices(int A[N][N], int B[N][N], int C[N][N]) {
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

// Function to print a matrix
void printMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];
    struct timespec start_ts, end_ts, diff_ts;

    initMatrix(A);
    initMatrix(B);

    clock_gettime(CLOCK_MONOTONIC, &start_ts);
    multiplyMatrices(A, B, C);
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
