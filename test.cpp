#define CATCH_CONFIG_MAIN
#include "longnum.h"
#include "catch_amalgamated.hpp"


#define CHECK_WITH_OUTPUT(expr) \
do { \
    if (expr) { \
        std::cout << "OK: " << #expr << "\n"; \
    } else { \
        std::cout << "FAIL: " << #expr << "\n"; \
    } \
        CHECK(expr); \
} while (0)

// Сохранить given->when->then

TEST_CASE("Проверка Сложения", "[longnum]") {
    // --- GIVEN --- //
    // Обычное сложение
    LongNum a_11("123.5"), b_11("45.25"), expr_11("168.75"), result_11;
    LongNum a_12("123.5"), b_12("-45.25"), expr_12("78.25"), result_12;
    LongNum a_13("45.5"), b_13("-123.25"), expr_13("-77.75"), result_13;
    LongNum a_14("45.25"), b_14("-123.5"), expr_14("-78.25"), result_14;
    // Сложение с беск. периодической дробью
    LongNum a_21("123.2"), b_21("45.25"), expr_21("168.45"), result_21;
    LongNum a_22("0.123"), b_22("123"), expr_22("123.123"), result_22;
    // Проверка ну нуль
    LongNum a_31("0.000001"), b_31("-0.000001"), result_31;
    LongNum a_32("0"), result_32;
    LongNum a_33("0.00000000000000000000000001"), b_33("0"), result_33;
    // --- WHEN --- //        // --- THEN --- ///
    result_11 = a_11 + b_11; CHECK_WITH_OUTPUT((result_11 - expr_11).isNull());
    result_12 = a_12 + b_12; CHECK_WITH_OUTPUT((result_12 - expr_12).isNull());
    result_13 = a_13 + b_13; CHECK_WITH_OUTPUT((result_13 - expr_13).isNull());
    result_14 = a_14 + b_14; CHECK_WITH_OUTPUT((result_14 - expr_14).isNull());
    result_21 = a_21 + b_21; CHECK_WITH_OUTPUT((result_21 - expr_21).isNull());
    result_22 = a_22 + b_22; CHECK_WITH_OUTPUT((result_22 - expr_22).isNull());
    result_31 = a_31 + b_31; CHECK_WITH_OUTPUT(result_31.isNull());
    result_32 = a_32;        CHECK_WITH_OUTPUT(result_32.isNull());
    result_33 = a_33 + b_33; CHECK_WITH_OUTPUT(result_33.isNull());
}

TEST_CASE("Проверка Вычитания", "[longnum]") {

    // --- GIVEN --- //
    // Обычное вычитание
    LongNum a_11("123.5"), b_11("45.25"), expr_11("78.25"), result_11;
    LongNum a_12("123.5"), b_12("-45.25"), expr_12("168.75"), result_12;
    LongNum a_13("45.5"), b_13("-123.25"), expr_13("168.75"), result_13;
    LongNum a_14("45.25"), b_14("-123.5"), expr_14("168.75"), result_14;
    // Вычитание с беск. периодической дробью
    LongNum a_21("123.25"), b_21("45.2"), expr_21("78.05"), result_21;
    LongNum a_22("123.123"), b_22("0.123"), expr_22("123"), result_22;
    LongNum a_23("123.123"), b_23("123"), expr_23("0.123"), result_23;
    // Проверка ну нуль
    LongNum a_31("0.000001"), b_31("0.000001"), result_31;
    LongNum a_33("0"), b_33("0.000000000000000000000000000000001"), result_33;

    // --- WHEN --- //        // --- THEN --- ///
    result_11 = a_11 - b_11; CHECK_WITH_OUTPUT((result_11 - expr_11).isNull());
    result_12 = a_12 - b_12; CHECK_WITH_OUTPUT((result_12 - expr_12).isNull());
    result_13 = a_13 - b_13; CHECK_WITH_OUTPUT((result_13 - expr_13).isNull());
    result_14 = a_14 - b_14; CHECK_WITH_OUTPUT((result_14 - expr_14).isNull());
    result_21 = a_21 - b_21; CHECK_WITH_OUTPUT((result_21 - expr_21).isNull());
    result_22 = a_22 - b_22; CHECK_WITH_OUTPUT((result_22 - expr_22).isNull());
    result_23 = a_23 - b_23; CHECK_WITH_OUTPUT((result_23 - expr_23).isNull());
    result_31 = a_31 - b_31; CHECK_WITH_OUTPUT(result_31.isNull());
    result_33 = a_33 - b_33; CHECK_WITH_OUTPUT(result_33.isNull());
}

TEST_CASE("Проверка Умножения", "[longnum]") {

    // --- GIVEN --- //
    // Обычное умножение
    LongNum a_11("123.5"), b_11("45.25"), expr_11("5588.375"), result_11;
    LongNum a_12("123.25"), b_12("-45.5"), expr_12("-5607.875"), result_12;
    LongNum a_13("45.5"), b_13("1000"), expr_13("45500"), result_13;
    LongNum a_14("-45.25"), b_14("1"), expr_14("-45.25"), result_14;
    // Умножение с беск. периодической дробью
    LongNum a_21("123.25"), b_21("45.2"), expr_21("5570.9"), result_21;
    LongNum a_22("123.123"), b_22("0.123"), expr_22("15.144129"), result_22;
    LongNum a_23("123.123"), b_23("456.456"), expr_23("56200.232088"), result_23;
    // Проверка ну нуль
    LongNum a_31("0.000001"), b_31("0.000001"), result_31;
    LongNum a_33("0"), b_33("2412445125435235345254353454532453"), result_33;

    // --- WHEN --- //        // --- THEN --- ///
    result_11 = a_11 * b_11; CHECK_WITH_OUTPUT((result_11 - expr_11).isNull());
    result_12 = a_12 * b_12; CHECK_WITH_OUTPUT((result_12 - expr_12).isNull());
    result_13 = a_13 * b_13; CHECK_WITH_OUTPUT((result_13 - expr_13).isNull());
    result_14 = a_14 * b_14; CHECK_WITH_OUTPUT((result_14 - expr_14).isNull());
    result_21 = a_21 * b_21; CHECK_WITH_OUTPUT((result_21 - expr_21).isNull());
    result_22 = a_22 * b_22; CHECK_WITH_OUTPUT((result_22 - expr_22).isNull());
    result_23 = a_23 * b_23; CHECK_WITH_OUTPUT((result_23 - expr_23).isNull());
    result_31 = a_31 * b_31; CHECK_WITH_OUTPUT(result_31.isNull());
    result_33 = a_33 * b_33; CHECK_WITH_OUTPUT(result_33.isNull());
}

TEST_CASE("Проверка Деления", "[longnum]") {

    // --- GIVEN --- //
    // Обычное вычитание
    LongNum a_11("125.5"), b_11("0.5"), expr_11("251"), result_11;
    LongNum a_12("123123.25"), b_12("-123"), expr_12("-1001.00203252"), result_12;
    LongNum a_13("45.5"), b_13("1000"), expr_13("0.0455"), result_13;
    LongNum a_14("-45.25"), b_14("1"), expr_14("-45.25"), result_14;
    // Сложение с беск. периодической дробью
    LongNum a_21("123.25"), b_21("45.2"), expr_21("2.726769911504425"), result_21;
    LongNum a_22("123.123"), b_22("0.123"), expr_22("1001"), result_22;
    LongNum a_23("123.123"), b_23("456.456"), expr_23("0.269736842105"), result_23;
    // Проверка ну нуль
    LongNum a_31("0"), b_31("9453451453642834876434917823647816487126478264"), result_31;
    // !!!Важно: Программа не завершает работу при делении на 0, а просто возвр. 0
    LongNum a_33("2412445125435235345254353454532453"), b_33("0"), result_33;

    // --- WHEN --- //        // --- THEN --- ///
    result_11 = a_11 / b_11; CHECK_WITH_OUTPUT((result_11 - expr_11).isNull());
    result_12 = a_12 / b_12; CHECK_WITH_OUTPUT((result_12 - expr_12).isNull());
    result_13 = a_13 / b_13; CHECK_WITH_OUTPUT((result_13 - expr_13).isNull());
    result_14 = a_14 / b_14; CHECK_WITH_OUTPUT((result_14 - expr_14).isNull());
    result_21 = a_21 / b_21; CHECK_WITH_OUTPUT((result_21 - expr_21).isNull());
    result_22 = a_22 / b_22; CHECK_WITH_OUTPUT((result_22 - expr_22).isNull());
    result_23 = a_23 / b_23; CHECK_WITH_OUTPUT((result_23 - expr_23).isNull());
    result_31 = a_31 / b_31; CHECK_WITH_OUTPUT(result_31.isNull());
    result_33 = a_33 / b_33; CHECK_WITH_OUTPUT(result_33.isNull());
    result_12.print_ln();
    result_12.print_dec();
    expr_12.print_dec();
    expr_12.print_ln();
}
