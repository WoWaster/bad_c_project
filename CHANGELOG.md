# Changelog

## Unreleased

- починили `multiply_by_two` и форматирование, CI снова зелёный
- вернули статистику: `stats_mean`, `stats_median`, `stats_variance`
- тесты на `math_cli`
- удалили `src/Calc.c`, `src/legacy_math.c` и неиспользуемый `math_op_t`
- убрали `build/` из git

## 0.4.0 - 2019-11-14

- переехали на cmake
- поставили cmocka, написали первые тесты
- переехали на WebKit в clang-format

## 0.3.1 - 2019-06-02

- починили сборку на macOS
- вернули `math_cli`

## 0.3.0 - 2019-05-20

- попробовали сделать классы, не вышло
- вернулись к обычным функциям
