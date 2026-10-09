/*
 *  Юнит-тесты для stats. Устроены так же, как test_math_utils.c:
 *  каждый тест можно запустить по имени, ctest видит их по отдельности.
 */
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <cmocka.h>

#include "stats.h"

#define EPS 1e-9

/* ----------------------------------------------------------------- mean */

static void test_mean_of_empty_is_zero(void** state)
{
    (void)state;
    assert_float_equal(stats_mean(NULL, 0), 0.0, EPS);
}

static void test_mean_of_single_value(void** state)
{
    (void)state;
    int values[] = { 7 };
    assert_float_equal(stats_mean(values, 1), 7.0, EPS);
}

static void test_mean_is_fractional(void** state)
{
    (void)state;
    int values[] = { 1, 2 };
    assert_float_equal(stats_mean(values, 2), 1.5, EPS);
}

static void test_mean_of_negative_values(void** state)
{
    (void)state;
    int values[] = { -1, -2, -3 };
    assert_float_equal(stats_mean(values, 3), -2.0, EPS);
}

/* --------------------------------------------------------------- median */

static void test_median_of_empty_is_zero(void** state)
{
    (void)state;
    assert_float_equal(stats_median(NULL, 0), 0.0, EPS);
}

static void test_median_of_odd_count_unsorted(void** state)
{
    (void)state;
    int values[] = { 9, 1, 5 };
    assert_float_equal(stats_median(values, 3), 5.0, EPS);
}

static void test_median_of_even_count_is_average_of_middle(void** state)
{
    (void)state;
    int values[] = { 4, 1, 3, 2 };
    assert_float_equal(stats_median(values, 4), 2.5, EPS);
}

static void test_median_does_not_modify_input(void** state)
{
    (void)state;
    int values[] = { 3, 1, 2 };
    stats_median(values, 3);
    assert_int_equal(values[0], 3);
    assert_int_equal(values[1], 1);
    assert_int_equal(values[2], 2);
}

/* ------------------------------------------------------------- variance */

static void test_variance_of_empty_is_zero(void** state)
{
    (void)state;
    assert_float_equal(stats_variance(NULL, 0), 0.0, EPS);
}

static void test_variance_of_equal_values_is_zero(void** state)
{
    (void)state;
    int values[] = { 5, 5, 5 };
    assert_float_equal(stats_variance(values, 3), 0.0, EPS);
}

static void test_variance_of_known_set(void** state)
{
    (void)state;
    int values[] = { 2, 4, 4, 4, 5, 5, 7, 9 };
    assert_float_equal(stats_variance(values, 8), 4.0, EPS);
}

#define STATS_TESTS(X)                                \
    X(test_mean_of_empty_is_zero)                     \
    X(test_mean_of_single_value)                      \
    X(test_mean_is_fractional)                        \
    X(test_mean_of_negative_values)                   \
    X(test_median_of_empty_is_zero)                   \
    X(test_median_of_odd_count_unsorted)              \
    X(test_median_of_even_count_is_average_of_middle) \
    X(test_median_does_not_modify_input)              \
    X(test_variance_of_empty_is_zero)                 \
    X(test_variance_of_equal_values_is_zero)          \
    X(test_variance_of_known_set)

/* группа из одного теста, для запуска по имени */
#define DEFINE_TEST_GROUP(fn) \
    static const struct CMUnitTest fn##_group[] = { cmocka_unit_test(fn) };

STATS_TESTS(DEFINE_TEST_GROUP)

#undef DEFINE_TEST_GROUP

/* все тесты разом */
#define ADD_TO_ALL_TESTS(fn) cmocka_unit_test(fn),
static const struct CMUnitTest all_tests[] = {
    STATS_TESTS(ADD_TO_ALL_TESTS)
};
#undef ADD_TO_ALL_TESTS

int main(int argc, char** argv)
{
    if (argc > 1) {
#define RUN_TEST_IF_NAME_MATCHES(fn)                           \
    if (strcmp(argv[1], #fn) == 0) {                           \
        return cmocka_run_group_tests(fn##_group, NULL, NULL); \
    }

        STATS_TESTS(RUN_TEST_IF_NAME_MATCHES)

#undef RUN_TEST_IF_NAME_MATCHES

        fprintf(stderr, "unknown test: %s\n", argv[1]);
        return 2;
    }

    return cmocka_run_group_tests(all_tests, NULL, NULL);
}
