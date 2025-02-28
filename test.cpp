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
    // Обычное деление
    LongNum a_11("125.5"), b_11("0.5"), expr_11("251"), result_11;
    LongNum a_12("123123.25"), b_12("-123"), expr_12("-1001.002032520325203252"), result_12;
    LongNum a_13("45.5"), b_13("1000"), expr_13("0.0455"), result_13;
    LongNum a_14("-45.25"), b_14("1"), expr_14("-45.25"), result_14;
    LongNum a_21("123.25"), b_21("45.2"), expr_21("2.726769911504425"), result_21;
    LongNum a_22("123.123"), b_22("0.123"), expr_22("1001"), result_22;
    LongNum a_23("123.123"), b_23("456.456"), expr_23("0.269736842105"), result_23;
    LongNum a_24("26915408737435677.435177034647577"), b_24("97654243.629348562");
    LongNum expr_24("275619448.13780363942216762"), result_24;
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
    result_24 = a_24 / b_24; CHECK_WITH_OUTPUT((result_24 - expr_24).isNull());
    result_31 = a_31 / b_31; CHECK_WITH_OUTPUT(result_31.isNull());
    result_33 = a_33 / b_33; CHECK_WITH_OUTPUT(result_33.isNull());
}

TEST_CASE("Проверка Булевых Операций", "[longnum]") {
    // --- GIVEN --- //
    LongNum a1("12345.2"), b1("12345.2000001");
    LongNum a2("0.0000000000000000000000000000000001"), b2("0");
    LongNum a3("-12345.2"), b3("-12345.200000000000000000000000000000001");
    LongNum a4("-12345.2000001"), b4("12345.2000001");
    LongNum a5("0"), b5("-0.000000000000000001");
    LongNum a6("123456.123456"), b6("123456.123457");
    LongNum a7("456789"), b7("123456789");
    LongNum a8("123456789.999"), b8("123456789");
    LongNum a9("123456.123456"), b9("123456.123456");

    // --- Равенство / Не равенство --- //
    CHECK_WITH_OUTPUT(a1 != b1);
    CHECK_WITH_OUTPUT(a2 == b2);
    CHECK_WITH_OUTPUT(a3 == b3);
    CHECK_WITH_OUTPUT(a4 != b4);
    CHECK_WITH_OUTPUT(a5 != b5);
    CHECK_WITH_OUTPUT(a6 != b6);
    CHECK_WITH_OUTPUT(a7 != b7);
    CHECK_WITH_OUTPUT(a8 != b8);
    CHECK_WITH_OUTPUT(a9 == b9);
    // --- Больше / Меньше --- //
    CHECK_WITH_OUTPUT(a1 < b1);
    CHECK_WITH_OUTPUT(a2 >= b2);
    CHECK_WITH_OUTPUT(a2 <= b2);
    CHECK_WITH_OUTPUT(a3 <= b3);
    CHECK_WITH_OUTPUT(a3 >= b3);
    CHECK_WITH_OUTPUT(a4 < b4);
    CHECK_WITH_OUTPUT(a5 > b5);
    CHECK_WITH_OUTPUT(a6 < b6);
    CHECK_WITH_OUTPUT(a7 < b7);
    CHECK_WITH_OUTPUT(a8 > b8);
    CHECK_WITH_OUTPUT(a9 <= b9);
    CHECK_WITH_OUTPUT(a9 >= b9);
}

TEST_CASE("Проверка Конструкторов, Литерала и Вывода", "[longnum]") {
    LongNum a; a.print_dec(); a.print_ln();
    LongNum b(123.456); b.print_dec(3); b.print_ln();
    LongNum c("123456789.123456789"); c.print_dec(9); c.print_ln();
    LongNum d = 12398723453.753719322_longnum; d.print_dec(9); d.print_ln();
    LongNum e(b); e.print_dec(); e.print_ln(); // e.print_dec() демонстрирует вывод, если не поставить точность
    LongNum f = c; f.print_dec(); f.print_ln();
}

TEST_CASE("Проверка isNull, StrToBin, cmp_long_num", "[longnum]") {
    LongNum a, b(0), c("0"), d("0.0000000000000000000000000000000000000001");
    LongNum x("123.123"), y("123.1231"), z("-123.123"), w("-123.123");
    LongNum g("12345678998654321.123456789");

    CHECK_WITH_OUTPUT(a.isNull());
    CHECK_WITH_OUTPUT(b.isNull());
    CHECK_WITH_OUTPUT(c.isNull());
    CHECK_WITH_OUTPUT(d.isNull());
    CHECK_WITH_OUTPUT(cmp_long_num(x,y) == -1);
    // Замечание эта функция сравнивает abs значения, поэтому == 0
    CHECK_WITH_OUTPUT(cmp_long_num(x,z) == 0);
    CHECK_WITH_OUTPUT(cmp_long_num(y,z) == 1);
    CHECK_WITH_OUTPUT(cmp_long_num(z,w) == 0);

    // функция StrToBin используется внутри конструктора
    // и она ничего не выводит ни в терминал, ни в число, ни в класс
    // По сути StrToBin проверяется конструктором

}

// И выводит и считает пи
LongNum compute_pi_bbp(int precision, int iterations, int out_pres) {
    LongNum pi("0", precision);
    LongNum sixteen("16", precision);
    LongNum one("1", precision);
    LongNum two("2", precision);
    LongNum four("4", precision);
    LongNum power("1", precision);

    for (long k = 0; k < iterations; ++k) {
        LongNum divisor1(8 * k + 1, precision);
        LongNum divisor2(8 * k + 4, precision);
        LongNum divisor3(8 * k + 5, precision);
        LongNum divisor4(8 * k + 6, precision);

        LongNum term1 = four * divisor2 * divisor3 * divisor4;
        LongNum term2 = two * divisor1 * divisor3 * divisor4;
        LongNum term3 = one * divisor1 * divisor2 * divisor4;
        LongNum term4 = one * divisor1 * divisor2 * divisor3;

        LongNum term_tmp = term1 - term2 - term3 - term4;
        LongNum general_divisor = divisor1 * divisor2 * divisor3 * divisor4 * power;


        LongNum term = term_tmp / general_divisor;
        // LongNum term = (term1 - term2 - term3 - term4) / power;
        pi = pi + term;
        power = power * sixteen;
    }
    // Выводим результат с out_pres цифрами после запятой
    std::cout << "Pi: ";
    pi.print_dec(out_pres);
    std::cout << std::endl;
    return pi;
}

TEST_CASE("Вычисление Пи", "[longnum]") {
    // Устанавливаем точность (количество бит)
    int precision = 110; // двоичная точность вычисления
    int out_pres = 80; // ДЕСЯТИЧНАЯ точность вывода
    // Количество итераций
    int iterations = 100;
    // Вычисляем π
    LongNum pi = compute_pi_bbp(precision, iterations, out_pres);
}