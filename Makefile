CC=gcc

TARGETS=naive_matmul naive_matmul_opt \
	cache_aware_matmul cache_aware_matmul_opt \
	single_load_matmul single_load_matmul_opt

CFLAGS_NO_OPTIMIZE = -Wall
CFLAGS_OPTIMIZE = -O3 -march=native -fno-tree-vectorize
CPPFLAGS =
UTILS_OBJ = matmul_utils.o

N ?= 512
BLOCK_SIZE ?= 64

# naive
CFLAGS_naive_matmul = $(CFLAGS_NO_OPTIMIZE)
CPPFLAGS_naive_matmul = $(CPPFLAGS)
CFLAGS_naive_matmul_opt = $(CFLAGS_OPTIMIZE)
CPPFLAGS_naive_matmul_opt = $(CPPFLAGS)

# cache aware
CFLAGS_cache_aware_matmul = $(CFLAGS_NO_OPTIMIZE)
CPPFLAGS_cache_aware_matmul = $(CPPFLAGS) -DBLOCK_SIZE=$(BLOCK_SIZE) 
CFLAGS_cache_aware_matmul_opt = $(CFLAGS_OPTIMIZE)
CPPFLAGS_cache_aware_matmul_opt = $(CPPFLAGS_cache_aware_matmul)

# cache aware, single load/store per sub-block
CFLAGS_single_load_matmul = $(CFLAGS_NO_OPTIMIZE)
CPPFLAGS_single_load_matmul = $(CPPFLAGS) -DBLOCK_SIZE=$(BLOCK_SIZE) -DOPT_LOAD_STORE_OPS=true
CFLAGS_single_load_matmul_opt = $(CFLAGS_OPTIMIZE)
CPPFLAGS_single_load_matmul_opt = $(CPPFLAGS_single_load_matmul)



all: $(TARGETS)

$(UTILS_OBJ): matmul_utils.c
	$(CC) -c matmul_utils.c -o $(UTILS_OBJ)

single_load_matmul: cache_aware_matmul.c $(UTILS_OBJ)
	$(CC) $(CFLAGS_$@) $(CPPFLAGS_$@) -o $@ $^

single_load_matmul_opt: cache_aware_matmul.c $(UTILS_OBJ)
	$(CC) $(CFLAGS_$@) $(CPPFLAGS_$@) -o $@ $^

%: %.c $(UTILS_OBJ)
	$(CC) $(CFLAGS_$@) $(CPPFLAGS_$@) -o $@ $^

%_opt: %.c $(UTILS_OBJ)
	$(CC) $(CFLAGS_$@) $(CPPFLAGS_$@) -o $@ $^

.PHONY: test
test: clean all
	@echo "+--------------------------+-------------+"
	@printf "|   Results for N=%-8d |  Time (ms)  |\n" ${N}
	@echo "+--------------------------+-------------+"
	@for target in ${TARGETS}; do \
		printf "| %-24s | %11d |\n" $${target} $$(./$${target} ${N}); \
	done
	@echo "+--------------------------+-------------+"
	@echo "see <program>.log for input and output matrices"

clean:
	rm -f $(TARGETS) $(UTILS_OBJ)