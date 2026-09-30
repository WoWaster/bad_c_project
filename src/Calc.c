#include "Calc.h"
#include "math_utils.h"

int calculate_sum_and_double(int a, int b)
{
    int result = add(a, b);
    return multiply_by_two(result);
}
