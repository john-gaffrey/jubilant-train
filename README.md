# jubilant-train
This is a submission for TLF mentorship "Port & Polish: Software Optimization for RISC-V - UNPAID"

Compares two implmentations of matrix multiplication.

## Instructions:
- `git clone https://github.com/john-gaffrey/jubilant-train && cd ./jubilant-train`
- `make test`

Expected output:
``` bash
$ make test
gcc -c matmul_utils.c -o matmul_utils.o
gcc -Wall  -o naive_matmul naive_matmul.c matmul_utils.o
gcc -O3 -march=native -fno-tree-vectorize  -o naive_matmul_opt naive_matmul.c matmul_utils.o
gcc -Wall  -DBLOCK_SIZE=64 -o cache_aware_matmul cache_aware_matmul.c matmul_utils.o
gcc -O3 -march=native -fno-tree-vectorize  -DBLOCK_SIZE=64 -o cache_aware_matmul_opt cache_aware_matmul.c matmul_utils.o
gcc -Wall  -DBLOCK_SIZE=64 -DOPT_LOAD_STORE_OPS=true -o single_load_matmul cache_aware_matmul.c matmul_utils.o
gcc -O3 -march=native -fno-tree-vectorize  -DBLOCK_SIZE=64 -DOPT_LOAD_STORE_OPS=true -o single_load_matmul_opt cache_aware_matmul.c matmul_utils.o
+--------------------------+-------------+
|   Results for N=512      |  Time (ms)  |
+--------------------------+-------------+
| naive_matmul             |         628 |
| naive_matmul_opt         |         105 |
| cache_aware_matmul       |         506 |
| cache_aware_matmul_opt   |          87 |
| single_load_matmul       |         353 |
| single_load_matmul_opt   |          75 |
+--------------------------+-------------+
```

### Other commands:
- `make test BLOCK_SIZE=128`
    - overrides the block size for the cache aware implementations. Default is 64.
- `make test N=1024`
    - runs tests a 1024x1024 matrix. Default is 512.
- `make test MAX_MATRIX_VAL=200`
    - overrides the upper bound for the random input initialization. Default is 100.
- `make clean`
    - deletes all targets. `make test` currently includes this for better user experience when changing build options.
- `make all`
    - builds all targets, does not run the tests

### Details
Each program initalizes the input arrays to a random positive int, limited by MAX_MATRIX_VAL. The output matrix is initialized to 0.
The programs output the clock time of the multiplication to stdout, skipping initialization, logging and free operations.

### Program Details
- naive_matmul: naive triple nested loop matrix multiplication.
- cache_aware_matmul: uses a blocking approach to efficiently manipualte values in the cache.
- single_load_matmul: same as cache_aware_matmul, but also optimizes the accumulator access.
