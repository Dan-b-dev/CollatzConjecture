#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <inttypes.h>
#define DOMAIN_UPPER_BOUND 1000000000// upper bound of positive integer inputs into the function
#define MAX_MEMO 1500

bool overflow_detected (uint64_t peak) {
    return (peak > (UINT64_MAX - 1) / 3);
}

void compute_collatz(uint64_t n, uint64_t *peak, uint64_t *stopping_time, uint64_t *memo, uint64_t *trajectory) {
    *peak = n;
    *stopping_time = 0;
    uint64_t length = 0;
    
    while (n != 1) {
        if (overflow_detected(n)) {
            printf("overflow at %" PRIu64, n);
            exit(EXIT_FAILURE);
        }

        trajectory[length++] = n;

        if (n % 2 == 1) {
            n = 3 * n + 1;
        }

        else {
            n /= 2;
        }
        (*stopping_time)++;

        if (n > *peak) {
            *peak = n;
        }


        if (n < MAX_MEMO && memo[n] != 0) {
            *stopping_time += memo[n] - 1;
            break;
        }
    }

    if (length >= MAX_MEMO) {
        fprintf(stderr, "Trajectory buffer overflow\n");
        exit(EXIT_FAILURE);
    }

    for (uint64_t i = 0; i < length; i++) {
        if (trajectory[i] < MAX_MEMO) {
               memo[trajectory[i]] = *stopping_time - i + 1;
        }
    } 
}

void find_peak (uint64_t initial_value, uint64_t *peak, uint64_t *current_record) {;
    if (*peak > *current_record ) {
        *current_record = *peak; 
        printf("index: %" PRIu64 " record: %" PRIu64 "\n", initial_value, *current_record);
    }
}

void find_stopping_time (uint64_t initial_value, uint64_t *stopping_time, uint64_t *current_record) {;
    if (*stopping_time > *current_record ) {
        *current_record = *stopping_time; 
        printf("index: %" PRIu64 " record: %" PRIu64 "\n", initial_value, *current_record);
        
    }
}

int main(void) {
    uint64_t current_record = 0;
    uint64_t peak;
    uint64_t stopping_time;
    uint64_t *memo = calloc(MAX_MEMO, sizeof(uint64_t));
    uint64_t *trajectory = malloc(MAX_MEMO * sizeof(uint64_t));
    memo[1] = 1;
    clock_t start = clock();

    for (uint64_t initial_value = 1; initial_value <= DOMAIN_UPPER_BOUND; initial_value++) {
        compute_collatz(initial_value, &peak, &stopping_time, memo, trajectory);
        find_stopping_time(initial_value, &stopping_time, &current_record);
    }

    free(memo);
    
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nRuntime: %.6f seconds\n", seconds);
}
