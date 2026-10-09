#ifndef STATS_H
#define STATS_H

#include <stddef.h>

// описательная статистика по массиву int
// для пустого массива (count == 0) все функции возвращают 0.0

double stats_mean(const int* values, size_t count);
double stats_median(const int* values, size_t count);
double stats_variance(const int* values, size_t count);

#endif /* STATS_H */
