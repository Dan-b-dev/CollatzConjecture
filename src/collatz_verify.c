#include "Collatz.h"

bool overflow_detected (uint64_t peak) {
    return (peak > (UINT64_MAX - 1) / 3);
}

void verify_collatz(uint64_t n){
    uint64_t initial = n;
    while (n != 1) {
        if (overflow_detected(n)) {
            printf("overflow at %" PRIu64, n);
            exit(EXIT_FAILURE);
        }

        if (n % 2 == 1) {
            n = 3 * n + 1;
        }

        else {
            n /= 2;
        }

          if (n < initial) {
            break;
        }
    }
}