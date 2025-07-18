#include "matmul_utils.h"

// calculates the difference between a start and end time
void calculate_ts_difference(struct timespec *start_ts,
                             struct timespec *end_ts,
                             struct timespec *diff_ts) {
    diff_ts->tv_sec = diff_ts->tv_sec - start_ts->tv_sec;
    diff_ts->tv_nsec = diff_ts->tv_nsec - start_ts->tv_nsec;
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
