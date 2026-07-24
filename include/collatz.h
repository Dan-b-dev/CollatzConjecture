#ifndef COLLATZ_H
#define COLLATZ_H
#define DOMAIN_UPPER_BOUND 100000000
#define MAX_MEMO 1000

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    uint16_t stopping_time;
    uint64_t peak;
} memo_entry;

bool overflow_detected (
    uint64_t peak);

void find_peak (
    uint64_t initial_value, 
    uint64_t *peak, 
    uint64_t *current_record);

void find_stopping_time (
    uint64_t initial_value, 
    uint16_t *stopping_time, 
    uint64_t *current_record);

void compute_collatz(
    uint64_t n, 
    uint64_t *peak, 
    uint16_t *stopping_time, 
    memo_entry *memo, 
    uint64_t *trajectory);

void verify_collatz(
    uint64_t n);

#endif