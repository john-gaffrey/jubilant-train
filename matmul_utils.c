#include "matmul_utils.h"

#define MAX_MATRIX_VAL 100
#define LOG_FILE_SIZE 64

// calculates the difference between a start and end time
void calculate_ts_difference(struct timespec *start_ts,
                             struct timespec *end_ts,
                             struct timespec *diff_ts) {
    diff_ts->tv_sec = end_ts->tv_sec - start_ts->tv_sec;
    diff_ts->tv_nsec = end_ts->tv_nsec - start_ts->tv_nsec;
    if (end_ts->tv_nsec < start_ts->tv_nsec)
    {
        diff_ts->tv_sec -= 1;
        diff_ts->tv_nsec += 1000000000L;
    }
}

// returns the timespec time in milliseconds
int timespec_to_ms(struct timespec *ts) {
    return ts->tv_sec * 1000L + ts->tv_nsec/1000000;
}

void allocate_matrix(int ***matrix, int N) {
    *matrix = malloc(N * sizeof(int *));

    for (int i = 0; i < N; i++) {
        (*matrix)[i] = malloc(N * sizeof(int));
    }
}

void init_matrix_rand(int **matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % MAX_MATRIX_VAL;
        }
    }
}

void init_matrix_zero(int **matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = 0;
        }
    }
}

void free_matrix(int **matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

void print_usage(char* prog_name) {
    printf("Usage:\n");
    printf("%s N [LOG]\n", prog_name);
    printf("N: required - the size of square matrices to multiply\n");
    printf("LOG: optional, specifies the log file to write the matrix details to. \
            Defaults to %s.log\n", prog_name);
}

void print_matrix(int **matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_matrix_to_file(FILE *fp , int **matrix, int N) {
    fprintf(fp, "[");
    for (int i = 0; i < N; i++) {
        fprintf(fp, "[");
        for (int j = 0; j < N; j++) {
            fprintf(fp, "%d", matrix[i][j]);
            if (j != N-1) {
                fprintf(fp, ", ");
            }
        }
        fprintf(fp, "]");
        if (i != N-1) {
            fprintf(fp, ", ");
        }
    }
    fprintf(fp, "]\n");
}

int shared_main(int argc, char* argv[], void (*matmul_func)(int **, int **, int**, int)) {
    int N;
    int **A, **B, **C;
    char log_file[LOG_FILE_SIZE];

    char *endptr;
    struct timespec start_ts, end_ts, diff_ts;

    // parse args
    if (argc < 2) {
        printf("Not enough arguments\n");
        print_usage(argv[0]);
        return -1;
    }

    errno = 0;
    N = strtol(argv[1], &endptr, 10);

    if (errno == ERANGE) {
        printf("N: `%s` caused overflow/underflow, please try another value\n", argv[1]);
        return -1;
    } else if (endptr == argv[1]) {
        printf("N: `%s` has no digits, please try another value\n", argv[1]);
        return -1;
    }

    if (argc == 3) {
        strncpy(log_file, argv[2], LOG_FILE_SIZE);
    } else {
        sprintf(log_file, "%s.log", argv[0]);
    }

    // allocate and init matrices
    allocate_matrix(&A, N);
    allocate_matrix(&B, N);
    allocate_matrix(&C, N);

    // srand(time(NULL));
    init_matrix_rand(A, N);
    init_matrix_rand(B, N);
    init_matrix_zero(C, N);

    // run test and take measurements
    clock_gettime(CLOCK_MONOTONIC, &start_ts);
    matmul_func(A, B, C, N);
    clock_gettime(CLOCK_MONOTONIC, &end_ts);
    calculate_ts_difference(&start_ts, &end_ts, &diff_ts);

    // print for use by benchmarking in Makefile
    printf("%d\n", timespec_to_ms(&diff_ts));

    // print matrices to log
    FILE *fp = fopen(log_file, "w");
    if (fp == NULL) {
        printf("Failed to open file: `%s`\n", log_file);
    } else {
        fprintf(fp, "--- A ---\n");
        print_matrix_to_file(fp, A, N);
        fprintf(fp, "--- B ---\n");
        print_matrix_to_file(fp, B, N);
        fprintf(fp, "--- C ---\n");
        print_matrix_to_file(fp, C, N);
        fclose(fp);
    }
    

    // cleanup
    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);

    return 0;
}