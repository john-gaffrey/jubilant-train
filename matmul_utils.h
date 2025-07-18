#ifndef MATMUL_UTILS_H
#define MATMUL_UTILS_H

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int timespec_to_ms(struct timespec *ts);
void calculate_ts_difference(struct timespec *start_ts,
                             struct timespec *end_ts,
                             struct timespec *diff_ts);

void allocate_matrix(int ***matrix, int n);
void init_matrix_rand(int **matrix, int n);
void init_matrix_zero(int **matrix, int n);
void free_matrix(int **matrix, int n);

void print_usage(char* prog_name);
void print_matrix(int **matrix, int n);

int shared_main(int argc, char* argv[], void (*matmul_func)(int **, int **, int**, int));

#endif // MATMUL_UTILS_H