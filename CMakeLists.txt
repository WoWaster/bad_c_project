cmake_minimum_required(VERSION 3.16)

project(mathlib VERSION 0.4.0 LANGUAGES C)

# TODO: разобраться с типами сборок, пока хардкодим Release
set(CMAKE_BUILD_TYPE Release CACHE STRING "build type" FORCE)

add_compile_options(-Wall -Wextra)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(math_utils src/math_utils.c src/stats.c)
target_include_directories(math_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(math_cli src/main.c)
target_link_libraries(math_cli PRIVATE math_utils)

enable_testing()

find_path(CMOCKA_INCLUDE_DIR cmocka.h)
find_library(CMOCKA_LIBRARY NAMES cmocka)

if(NOT CMOCKA_INCLUDE_DIR OR NOT CMOCKA_LIBRARY)
  message(FATAL_ERROR "cmocka not found. Install it: sudo apt-get install libcmocka-dev")
endif()

add_executable(test_math_utils tests/test_math_utils.c)
target_include_directories(test_math_utils PRIVATE ${CMOCKA_INCLUDE_DIR})
target_link_libraries(test_math_utils PRIVATE math_utils ${CMOCKA_LIBRARY})

# каждый тест - отдельная проверка в ctest, чтобы в CI было видно имена
function(add_unit_test target name)
  add_test(NAME ${name} COMMAND ${target} ${name})
endfunction()

add_unit_test(test_math_utils test_add_of_positive_numbers)
add_unit_test(test_math_utils test_add_of_negative_numbers)
add_unit_test(test_math_utils test_add_of_zero_is_neutral)
add_unit_test(test_math_utils test_add_is_commutative)
add_unit_test(test_math_utils test_add_near_int_max)
add_unit_test(test_math_utils test_subtract_of_positive_numbers)
add_unit_test(test_math_utils test_subtract_of_equal_numbers_is_zero)
add_unit_test(test_math_utils test_subtract_of_negative_numbers)
add_unit_test(test_math_utils test_subtract_undoes_add)
add_unit_test(test_math_utils test_is_even_of_zero)
add_unit_test(test_math_utils test_is_even_of_positive_even)
add_unit_test(test_math_utils test_is_even_of_positive_odd)
add_unit_test(test_math_utils test_is_even_of_negative_even)
add_unit_test(test_math_utils test_is_even_of_negative_odd)
add_unit_test(test_math_utils test_is_even_of_int_min)
add_unit_test(test_math_utils test_multiply_by_two_of_zero_is_zero)
add_unit_test(test_math_utils test_multiply_by_two_of_one_is_two)
add_unit_test(test_math_utils test_multiply_by_two_of_two_is_four)
add_unit_test(test_math_utils test_multiply_by_two_of_ten_is_twenty)
add_unit_test(test_math_utils test_multiply_by_two_of_negative_three)
add_unit_test(test_math_utils test_multiply_by_two_of_negative_one_stays_negative)
add_unit_test(test_math_utils test_multiply_by_two_near_int_max)
add_unit_test(test_math_utils test_multiply_by_two_near_int_min)
add_unit_test(test_math_utils test_multiply_by_two_applied_twice_doubles_again)

add_executable(test_stats tests/test_stats.c)
target_include_directories(test_stats PRIVATE ${CMOCKA_INCLUDE_DIR})
target_link_libraries(test_stats PRIVATE math_utils ${CMOCKA_LIBRARY})

add_unit_test(test_stats test_mean_of_empty_is_zero)
add_unit_test(test_stats test_mean_of_single_value)
add_unit_test(test_stats test_mean_is_fractional)
add_unit_test(test_stats test_mean_of_negative_values)
add_unit_test(test_stats test_median_of_empty_is_zero)
add_unit_test(test_stats test_median_of_odd_count_unsorted)
add_unit_test(test_stats test_median_of_even_count_is_average_of_middle)
add_unit_test(test_stats test_median_does_not_modify_input)
add_unit_test(test_stats test_variance_of_empty_is_zero)
add_unit_test(test_stats test_variance_of_equal_values_is_zero)
add_unit_test(test_stats test_variance_of_known_set)

# тесты консольной утилиты: запускаем math_cli и сверяем вывод
function(add_cli_test name expected)
  add_test(NAME ${name} COMMAND math_cli ${ARGN})
  set_tests_properties(${name} PROPERTIES PASS_REGULAR_EXPRESSION "${expected}")
endfunction()

add_cli_test(test_cli_positive_numbers "sum = 7\ndiff = -1\na \\* 2 = 6\na is odd" 3 4)
add_cli_test(test_cli_negative_numbers "sum = -7\ndiff = -1\na \\* 2 = -8\na is even" -4 -3)
add_cli_test(test_cli_zeros "sum = 0\ndiff = 0\na \\* 2 = 0\na is even" 0 0)
add_cli_test(test_cli_without_arguments_prints_usage "usage: ")
add_cli_test(test_cli_with_one_argument_prints_usage "usage: " 1)
add_cli_test(test_cli_rejects_non_integer "error: arguments must be integers" 3 abc)
add_cli_test(test_cli_rejects_trailing_garbage "error: arguments must be integers" 3x 4)
