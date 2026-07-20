#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#define DOMAIN_UPPER_BOUND 100000000 // upper bound of positive integer inputs into the function

bool overflow_detected (uint64_t peak) {
    return (peak > (UINT64_MAX - 1) / 3);
}

void compute_collatz(uint64_t n, uint64_t *peak) {
    *peak = n;
    uint64_t initial_value = n;
    while (n != 1) {
        if (overflow_detected(n) == 1) {
            printf("overflow at %" PRIu64, n);
            break;
        }
        if (n % 2 == 1) {
            n = 3 * n + 1;
        }
        else {
            n /= 2;
        }
        if (n > *peak) {
            *peak = n;
        }
        if (n < initial_value) {
            break;
        }
    }
}

void find_peak_record (uint64_t initial_value, uint64_t *peak, uint64_t *current_record) {;
    if (*peak > *current_record ) {
        *current_record = *peak; 
        printf("index: %" PRIu64 " record: %" PRIu64 "\n", initial_value, *current_record);
    }
    
}

int main(void) {
    uint64_t current_record = 0;
    uint64_t peak;
    clock_t start = clock();
    for (uint64_t initial_value = 1; initial_value <= DOMAIN_UPPER_BOUND; initial_value++) {
        compute_collatz(initial_value, &peak);
        find_peak_record(initial_value, &peak, &current_record);
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nRuntime: %.6f seconds\n", seconds);
}
