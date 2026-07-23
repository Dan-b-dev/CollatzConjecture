#include "Collatz.h"

int main(void) {
    memo_entry *memo = calloc(MAX_MEMO, sizeof(memo_entry));
    uint64_t *trajectory = malloc(MAX_MEMO * sizeof(uint16_t));
    memo[1].peak = 1;
    memo[1].stopping_time = 1;
    uint64_t current_record = 0;
    uint64_t peak;
    uint16_t stopping_time;
    
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