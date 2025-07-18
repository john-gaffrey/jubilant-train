CC=gcc
ARGS_NO_OPTIMIZE=-Wall
ARGS_OPTIMIZE=-O3 -march=native -fno-tree-vectorize
TARGETS=naive_matmul naive_matmul_opt \
	cache_aware_matmul cache_aware_matmul_opt 
UTILS_OBJ = matmul_utils.o
N ?= 512

all: $(TARGETS)

$(UTILS_OBJ): matmul_utils.c
	$(CC) -c matmul_utils.c -o $(UTILS_OBJ)

naive_matmul: naive_matmul.c $(UTILS_OBJ)
	$(CC) $(ARGS_NO_OPTIMIZE) -o $@ $^

naive_matmul_opt: naive_matmul.c $(UTILS_OBJ)
	$(CC) $(ARGS_OPTIMIZE) -o $@ $^

cache_aware_matmul: cache_aware_matmul.c $(UTILS_OBJ)
	$(CC) $(ARGS_NO_OPTIMIZE) -o $@ $^

cache_aware_matmul_opt: cache_aware_matmul.c $(UTILS_OBJ)
	$(CC) $(ARGS_OPTIMIZE) -o $@ $^

.PHONY: test
test: all
	@echo "+--------------------------+-------------+"
	@printf "|   Results for N=%-8d |  Time (ms)  |\n" ${N}
	@echo "+--------------------------+-------------+"
	@for target in ${TARGETS}; do \
		printf "| %-24s | %11d |\n" $${target} $$(./$${target} ${N}); \
	done
	@echo "+--------------------------+-------------+"

clean:
	rm -f $(TARGETS) $(UTILS_OBJ)