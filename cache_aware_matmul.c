#include "matmul_utils.h"

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 64
#endif

#ifndef OPT_LOAD_STORE_OPS
#define OPT_LOAD_STORE_OPS false
#endif

void multiply_matrices_in_blocks(int **A, int **B, int **C, int N) {
    // Loop tiling for better cache usage
    for (int ii = 0; ii < N; ii += BLOCK_SIZE) {
        for (int jj = 0; jj < N; jj += BLOCK_SIZE) {
            for (int kk = 0; kk < N; kk += BLOCK_SIZE) {
                // Multiply sub-blocks
                for (int i = ii; i < ii + BLOCK_SIZE && i < N; i++) {
                    for (int j = jj; j < jj + BLOCK_SIZE && j < N; j++) {
                        // I found that optimizing the load/store operations
                        // had a large performance impact
                        if (OPT_LOAD_STORE_OPS == true) {
                            int sum = C[i][j];
                            for (int k = kk; k < kk + BLOCK_SIZE && k < N; k++) {
                                sum += A[i][k] * B[k][j];
                            }
                            C[i][j] = sum;
                        } else {
                            for (int k = kk; k < kk + BLOCK_SIZE && k < N; k++) {
                                C[i][j]+= A[i][k] * B[k][j];
                            }
                        } // end if optimize_load_store
                    } // end for j
                } // end for i
            } // end for kk
        } // end for jj
    } // end ii
}

int main(int argc, char* argv[]) {
    return shared_main(argc, argv, multiply_matrices_in_blocks);
}
