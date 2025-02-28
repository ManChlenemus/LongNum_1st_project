// #include "longnum.h"
// #include <iostream>
//
// int main(void) {
//
//
//
//     // LongNum number1 ("123.2", 105);
//     // // number1.print_ln();
//     // LongNum number2("45.25", 105);
//     // // number2.print_ln();
//     // LongNum number3 = number1 + number2;
//     // LongNum tmp(168.45);
//     // number3.print_ln();
//     // tmp.print_ln();
//     // number3 = number3 - tmp;
//     // number3.print_ln();
//     // number3.print_dec();
//     // std::cout << number3.isNull() << std::endl;
//
//     // LongNum a_11("123.5"), b_11("45.25"), expr_11("168.75"), result_11;
//     // LongNum a_12("123.5"), b_12("-45.25"), expr_12("78.75"), result_12;
//     // LongNum a_13("45.5"), b_13("-123.25"), expr_13("-77.75"), result_13;
//     // LongNum a_14("45.25"), b_14("-123.5"), expr_14("-78.75"), result_14;
//     // // Сложение с беск. периодической дробью
//     // LongNum a_21("123.2"), b_21("45.25"), expr_21("168.45"), result_21;
//     // LongNum a_22("0.123"), b_22("123"), expr_22("123.123"), result_22;
//     // // Проверка ну нуль
//     // LongNum a_31("0.000001"), b_31("-0.000001"), result_31;
//     // LongNum a_32("0"), result_32;
//     // LongNum a_33("0.00000000000000000000000001"), b_33("0"), result_33;
//     // result_11 = a_11 + b_11;
//     // result_12 = a_12 + b_12;
//     // result_13 = a_13 + b_13;
//     // result_14 = a_14 + b_14;
//     // result_21 = a_21 + b_21;
//     // result_22 = a_22 + b_22;
//     // result_31 = a_31 + b_31;
//     // result_32 = a_32;
//     // result_33 = a_33 + b_33;
//     //
//     // result_11.print_dec();
//     // result_12.print_dec();
//     // result_13.print_dec();
//     // result_14.print_dec();
//     // result_21.print_dec();
//     // result_22.print_dec();
//     // result_31.print_dec();
//     // result_32.print_dec();
//     // result_33.print_dec();
//     //
//
//
//
//     // // --- GIVEN --- //
//     // // Обычное вычитание
//     // LongNum a_11("123.5"), b_11("45.25"), expr_11("78.25"), result_11;
//     // LongNum a_12("123.5"), b_12("-45.25"), expr_12("168.75"), result_12;
//     // LongNum a_13("45.5"), b_13("-123.25"), expr_13("168.75"), result_13;
//     // LongNum a_14("45.25"), b_14("-123.5"), expr_14("168.75"), result_14;
//     // // Сложение с беск. периодической дробью
//     // LongNum a_21("123.25"), b_21("45.2"), expr_21("78.05"), result_21;
//     // LongNum a_22("123.123"), b_22("0.123"), expr_22("123"), result_22;
//     // LongNum a_23("123.123"), b_23("123"), expr_23("0.123"), result_23;
//     // // Проверка ну нуль
//     // LongNum a_31("0.000001"), b_31("0.000001"), result_31;
//     // LongNum a_33("0"), b_33("0.000000000000000000000000001"), result_33;
//     // // --- WHEN --- //        // --- THEN --- ///
//     // result_11 = a_11 - b_11; // CHECK_WITH_OUTPUT(result_11 == expr_11);
//     // result_12 = a_12 - b_12; // CHECK_WITH_OUTPUT(result_12 == expr_12);
//     // result_13 = a_13 - b_13; // CHECK_WITH_OUTPUT(result_13 == expr_13);
//     // result_14 = a_14 - b_14; // CHECK_WITH_OUTPUT(result_14 == expr_14);
//     // result_21 = a_21 - b_21; // CHECK_WITH_OUTPUT(result_21 == expr_21);
//     // result_22 = a_22 - b_22; // CHECK_WITH_OUTPUT(result_22 == expr_22);
//     // result_23 = a_23 - b_23; // CHECK_WITH_OUTPUT(result_23 == expr_23);
//     // result_31 = a_31 - b_31; // CHECK_WITH_OUTPUT(result_31.isNull());
//     // result_33 = a_33 - b_33; // CHECK_WITH_OUTPUT(result_33.isNull());
//
//     // LongNum number = 123.123_longnum;
//     // LongNum nnn = 1.0_longnum;
//     // number = number - nnn;
//     // //number = number - 1.0_longnum;
//     // number.print_dec(3);
//     // number.print_ln();
//
//     // LongNum numbyu("123.12312313");
//     // LongNum number(2);
//     // LongNum number2(3);
//     // LongNum number3 = number * number2;
//     // number.print_ln();
//     return 0;
// }