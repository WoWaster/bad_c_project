#include "math_utils.h"

// TODO: переписать на uint64_t, тут везде int

uint64_t add(uint64_t a, uint64_t b)
{
    return a + b;
}

uint64_t subtract(uint64_t a, uint64_t b)
{
    return a - b;
}

int64_t multiply_by_two(int64_t value)
{
    return value*2;
}

uint64_t is_even(uint64_t value)
{
    if (value % 2 == 0) {
        return 1;
    }

    return 0;
}
