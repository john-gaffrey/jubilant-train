CC=gcc
ARGS_NO_OPTIMIZE=-Wall
ARGS_OPTIMIZE=-O3 -march=native -fno-tree-vectorize
TARGETS=naive_matmul naive_matmul_opt \
	cache_aware_matmul cache_aware_matmul_opt 
N ?= 512

all: $(TARGETS)

naive_matmul: naive_matmul.c
	$(CC) $(ARGS_NO_OPTIMIZE) -o $@ $<

naive_matmul_opt: naive_matmul.c
	$(CC) $(ARGS_OPTIMIZE) -o $@ $<

cache_aware_matmul: cache_aware_matmul.c
	$(CC) $(ARGS_NO_OPTIMIZE) -o $@ $<

cache_aware_matmul_opt: cache_aware_matmul.c
	$(CC) $(ARGS_OPTIMIZE) -o $@ $<

.PHONY: test
test: all
	@echo "+--------------------------+-------------+"
	@printf "|   Results for N=%-8d |  Time (ms)  |\n" ${N}
	@echo "+--------------------------+-------------+"
	@for target in ${TARGETS}; do \
		printf "| %-24s | %11d |\n" $${target} $$(./$${target}); \
	done
	@echo "+--------------------------+-------------+"

clean:
	rm -f $(TARGETS)