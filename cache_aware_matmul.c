#include "matmul_utils.h"

#define BLOCK_SIZE 64 // Size of the block, tuned for cache

void multiply_in_blocks(int **A, int **B, int **C, int N) {
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
    return shared_main(argc, argv, multiply_in_blocks);
}
