#include <stdio.h>
#include <stdint.h>
#define DOMAIN_UPPER_BOUND 100000000 // upper bound of positive integer inputs into the function

typedef struct {
    int stopping_time;
    int64_t trajectory_max;
} data;

data collatz_data[DOMAIN_UPPER_BOUND];

void collatz(int64_t n, int *stopping_time, int64_t *trajectory_max) {
    *stopping_time = 0;
    *trajectory_max = n;
    while (n != 1) {
        if ( n % 2 == 1) {
            n = 3 * n + 1;
        }
        else {
            n /= 2;
        }
        (*stopping_time)++;
        if (n > *trajectory_max) {
            *trajectory_max = n;
        }
    }
}

void build_collatz_data (void) {
    int stopping_time;
    int64_t trajectory_max;
    for (int64_t i = 1; i <= DOMAIN_UPPER_BOUND; i++) {
        collatz(i, &stopping_time, &trajectory_max);
        collatz_data[i].trajectory_max = trajectory_max;
        collatz_data[i].stopping_time = stopping_time;
    }
}

void find_largest_peak(int64_t *peak_index, int64_t *peak) {
    *peak_index = 0;
    *peak = collatz_data[0].trajectory_max;
    for (int64_t i = 1; i <= DOMAIN_UPPER_BOUND; i++) {
        if (collatz_data[i].trajectory_max > *peak) {
            *peak = collatz_data[i].trajectory_max;
            *peak_index = i;
        }
    }
}

void find_largest_stopping_time(int64_t *stopping_time_index, int *stopping_time) {
    *stopping_time_index = 0;
    *stopping_time = collatz_data[0].stopping_time;
    for (int64_t i = 1; i <= DOMAIN_UPPER_BOUND; i++) {
        if (collatz_data[i].stopping_time > *stopping_time) {
            *stopping_time = collatz_data[i].stopping_time;
            *stopping_time_index = i;
        }
    }
}

int main(void) {
    int64_t largest_peak;
    int64_t largest_peak_number;
    int longest_stopping_time;
    int64_t longest_stopping_time_number;
    build_collatz_data();
    find_largest_peak(&largest_peak_number, &largest_peak);
    find_largest_stopping_time(&longest_stopping_time_number, &longest_stopping_time);
    printf("largest peak is %d, with a starting number of %d\n", largest_peak, largest_peak_number);
    printf("longest stopping time is %d, with a starting number of %d\n", longest_stopping_time, longest_stopping_time_number);
}
