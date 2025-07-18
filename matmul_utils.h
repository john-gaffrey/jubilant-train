#include <time.h>

void calculate_ts_difference(struct timespec *start_ts,
                             struct timespec *end_ts,
                             struct timespec *diff_ts);

int timespec_to_ms(struct timespec *ts);