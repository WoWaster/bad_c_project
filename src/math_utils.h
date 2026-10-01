#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// простые арифметические хелперы
// TODO: подумать про namespace, в C же нет namespace
#include <stdint.h>

typedef enum {
    MATH_OP_ADD,
    MATH_OP_SUBTRACT,
    MATH_OP_DOUBLE
} math_op_t;

uint64_t add(uint64_t a, uint64_t b);
uint64_t subtract(uint64_t a, uint64_t b);
int64_t multiply_by_two(int64_t value);
uint64_t is_even(uint64_t value);

#endif /* MATH_UTILS_H */
