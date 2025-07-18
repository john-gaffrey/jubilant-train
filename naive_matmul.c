#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "matmul_utils.h"

void multiply_matrices(int **A, int **B, int **C, int N) {
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
    return shared_main(argc, argv, multiply_matrices);
}
