# jubilant-train
This is a submission for TLF mentorship "Port & Polish: Software Optimization for RISC-V - UNPAID"

Compares two implmentations of matrix multiplication.

The matrices are randomly generated and logged to `<method>.log`
Note that the Time column shows the clock time of the multiplication itself, so it excludes the matrix initilization.

##Instructions:
- `git clone https://github.com/john-gaffrey/jubilant-train && cd ./jubilant-train`
- `make test`

Expected output:
```gcc -Wall -o naive_matmul naive_matmul.c
gcc -O3 -march=native -fno-tree-vectorize -o naive_matmul_opt naive_matmul.c
gcc -Wall -o cache_aware_matmul cache_aware_matmul.c
gcc -O3 -march=native -fno-tree-vectorize -o cache_aware_matmul_opt cache_aware_matmul.c
+--------------------------+-------------+
|   Results for N=512      |  Time (ms)  |
+--------------------------+-------------+
| naive_matmul             |        2506 |
| naive_matmul_opt         |         664 |
| cache_aware_matmul       |        1215 |
| cache_aware_matmul_opt   |         386 |
+--------------------------+-------------+```

Other commands:
- `make test N=1024`
    - runs tests a 1024x1024 matrix. Default is 512.
- `make clean`
- `make all`
    - builds all programs, does not run tests