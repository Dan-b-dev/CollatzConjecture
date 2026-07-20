#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#define DOMAIN_UPPER_BOUND 10000000 // upper bound of positive integer inputs into the function

typedef struct {
    uint64_t initial_value;
    uint64_t stopping_time;
    uint64_t peak;
} CollatzData; 

CollatzData collatz_data[DOMAIN_UPPER_BOUND];

void compute_collatz(uint64_t n, uint64_t *stopping_time, uint64_t *peak) {
    *stopping_time = 0;
    *peak = n;
    while (n != 1) {
        if ( n % 2 == 1) {
            n = 3 * n + 1;
        }
        else {
            n /= 2;
        }
        (*stopping_time)++;
        if (n > *peak) {
            *peak = n;
        }
    }
}

void build_collatz_data (void) {
    uint64_t stopping_time;
    uint64_t peak;
    for (uint64_t i = 1; i <= DOMAIN_UPPER_BOUND; i++) {
        compute_collatz(i, &stopping_time, &peak);
        collatz_data[i].initial_value = i;
        collatz_data[i].peak = peak;
        collatz_data[i].stopping_time = stopping_time;
    }
}

void find_peak_records () {
    uint64_t current_record = 0;
    for (uint64_t i = 1; i < DOMAIN_UPPER_BOUND; i++) {
        if (collatz_data[i].peak > current_record ) {
            current_record = collatz_data[i].peak; 
            printf("index: %" PRIu64 " record: %" PRIu64 "\n", collatz_data[i].initial_value, current_record);
          
        }
    }
}

void find_stopping_time_records () {
    uint64_t current_record = 0;
    for (uint64_t i = 1; i < DOMAIN_UPPER_BOUND; i++) {
        if (collatz_data[i].stopping_time > current_record) {
            current_record = collatz_data[i].stopping_time; 
            printf("index: %" PRIu64 " record: %" PRIu64 "\n", collatz_data[i].initial_value, current_record);
        }
    }
}

int main(void) {
    clock_t start = clock();
    build_collatz_data();
    find_peak_records();
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nRuntime: %.6f seconds\n", seconds);
}
