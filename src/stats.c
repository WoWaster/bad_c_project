#include "stats.h"

#include <stdlib.h>
#include <string.h>

static int compare_ints(const void* lhs, const void* rhs)
{
    int a = *(const int*)lhs;
    int b = *(const int*)rhs;
    return (a > b) - (a < b);
}

double stats_mean(const int* values, size_t count)
{
    if (count == 0) {
        return 0.0;
    }

    double sum = 0.0;
    for (size_t i = 0; i < count; i++) {
        sum += values[i];
    }
    return sum / count;
}

double stats_median(const int* values, size_t count)
{
    if (count == 0) {
        return 0.0;
    }

    int* sorted = malloc(count * sizeof(int));
    if (!sorted) {
        return 0.0;
    }
    memcpy(sorted, values, count * sizeof(int));
    qsort(sorted, count, sizeof(int), compare_ints);

    double median = count % 2 == 1
        ? sorted[count / 2]
        : ((double)sorted[count / 2 - 1] + sorted[count / 2]) / 2.0;

    free(sorted);
    return median;
}

// дисперсия генеральной совокупности (делим на count, а не на count - 1)
double stats_variance(const int* values, size_t count)
{
    if (count == 0) {
        return 0.0;
    }

    double mean = stats_mean(values, count);
    double sum = 0.0;
    for (size_t i = 0; i < count; i++) {
        double diff = values[i] - mean;
        sum += diff * diff;
    }
    return sum / count;
}
