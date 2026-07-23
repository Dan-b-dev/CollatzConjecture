#include "Collatz.h"

void compute_collatz(uint64_t n, uint64_t *peak, uint16_t *stopping_time, memo_entry *memo, uint64_t *trajectory) {
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

        if (n < MAX_MEMO && memo[n].stopping_time != 0) {
            *stopping_time += memo[n].stopping_time - 1;
             if (memo[n].peak > *peak) {
                *peak = memo[n].peak;
            }
            break;
        }
    }

    if (length >= MAX_MEMO) {
        printf("Trajectory buffer overflow\n");
        exit(EXIT_FAILURE);
    }

    for (uint64_t i = 0; i < length; i++) {
        if (trajectory[i] < MAX_MEMO) {
            memo[trajectory[i]].stopping_time = *stopping_time - i + 1;
            memo[trajectory[i]].peak = *peak;
        }
    } 
}

void find_peak (uint64_t initial_value, uint64_t *peak, uint64_t *current_record) {;
    if (*peak > *current_record ) {
        *current_record = *peak; 
        printf("index: %" PRIu64 " record: %" PRIu64 "\n", initial_value, *current_record);
    }
}

void find_stopping_time (uint64_t initial_value, uint16_t *stopping_time, uint64_t *current_record) {;
    if (*stopping_time > *current_record ) {
        *current_record = *stopping_time; 
        printf("index: %" PRIu64 " record: %" PRIu64 "\n", initial_value, *current_record);
        
    }
}
