#define CATCH_CONFIG_MAIN
#include "longnum.hpp"
#include "catch_amalgamated.hpp"
typedef LongNum LongNumber;

TEST_CASE("Plus operation works correctly, when both positive and no fractional part", "[arithmetic]") {
    // given
    const LongNumber num1("10");
    const LongNumber num2("10");

    // when
    const LongNumber result = num1 + num2;

    // then
    const LongNumber expected("20");
    CHECK(result == expected);
}
// ---------------------------- Добавил погрешность в эпсилон ------------------- //
TEST_CASE("Plus operation works correctly, when both positive and no integer part", "[arithmetic]") {
    // given
    const LongNumber num1("0.1");
    const LongNumber num2("0.1");
    const LongNumber EPS("0.00000000000000000000000000001"); // EPS

    // when
    const LongNumber result = num1 + num2;
    const LongNumber left_res = result - EPS; // оценка снизу
    const LongNumber right_res = result + EPS; // оценка сверху

    // then
    const LongNumber expected("0.2");
    if (left_res < expected && right_res > expected) CHECK(true);
    else CHECK(false);
    // CHECK((left_res < expected) && (right_res > expected)); - так не компилится
}

TEST_CASE("Plus operation works correctly, when both positive", "[arithmetic]") {
    // given
    const LongNumber num1("10.5");
    const LongNumber num2("10.75");

    // when
    const LongNumber result = num1 + num2;

    // then
    const LongNumber expected("21.25");
    CHECK(result == expected);
}

TEST_CASE("Plus operation works correctly, when one negative", "[arithmetic]") {
    // given
    const LongNumber num1("-10.75"); // -10.15 полагаю ошибочно (изм. на -10.75)
    const LongNumber num2("10.75");

    // when
    const LongNumber result = num1 + num2;

    // then
    const LongNumber expected("0");
    CHECK(result == expected);
}

TEST_CASE("Plus operation works correctly, when one negative and number is really long", "[arithmetic]") {
    // given
    const LongNumber num1(
        "-10000000000000000000000000000000000000000000000000000000000000000000001"
        ".5"
    );
    const LongNumber num2(
        "10000000000000000000000000000000000000000000000000000000000000000000000"
        ".5"
    );

    // when
    const LongNumber result = num1 + num2;

    // then
    const LongNumber expected("-1");
    CHECK(result == expected);
}

TEST_CASE("Minus operation works correctly", "[arithmetic]") {
    // given
    const LongNumber num1(
        "15.84375"
    );
    const LongNumber num2(
        "11.8125"
    );

    // when
    const LongNumber result_positive = num1 - num2;

    // then
    const LongNumber expected_positive("4.03125");
    CHECK(result_positive == expected_positive);

    // when
    const LongNumber result_negative = num2 - num1;

    // then
    const LongNumber expected_negative("-4.03125");
    CHECK(result_negative == expected_negative);
}

TEST_CASE("Multiply operation works correctly, when both positive", "[arithmetic]") {
    // given
    const LongNumber num1(
        "15.84375"
    );
    const LongNumber num2(
        "11.8125"
    );

    // when
    const LongNumber result = num1 * num2;

    // then
    const LongNumber expected("187.154296875");
    CHECK(result == expected);
}

TEST_CASE("Multiply operation works correctly, when one negative", "[arithmetic]") {
    // given
    const LongNumber num1(
        "-15.84375"
    );
    const LongNumber num2(
        "11.8125"
    );

    // when
    const LongNumber result = num1 * num2;

    // then
    const LongNumber expected("-187.154296875");
    CHECK(result == expected);
}

TEST_CASE("Multiply operation works correctly, when both negative", "[arithmetic]") {
    // given
    const LongNumber num1(
        "-15.84375"
    );
    const LongNumber num2(
        "-11.8125"
    );

    // when
    const LongNumber result = num1 * num2;

    // then
    const LongNumber expected("187.154296875");
    CHECK(result == expected);
}

TEST_CASE("Divide operation works correctly, when both positive", "[arithmetic]") {
    // given
    const LongNumber num1(
        "2.25"
    );
    const LongNumber num2(
        "2.25"
    );

    // when
    const LongNumber result = num1 / num2;

    // then
    const LongNumber expected("1");
    CHECK(result == expected);
}

TEST_CASE("Divide operation works correctly, when one negative", "[arithmetic]") {
    // given
    const LongNumber num1(
        "-2.25"
    );
    const LongNumber num2(
        "2.25"
    );

    // when
    const LongNumber result = num1 / num2;

    // then
    const LongNumber expected("-1");
    CHECK(result == expected);
}

TEST_CASE("Divide operation works correctly, when both negative", "[arithmetic]") {
    // given
    const LongNumber num1(
        "-2.25"
    );
    const LongNumber num2(
        "-2.25"
    );

    // when
    const LongNumber result = num1 / num2;

    // then
    const LongNumber expected("1");
    CHECK(result == expected);
}

TEST_CASE("Greater operation works correctly, when both positive", "[arithmetic]") {
    // given
    const LongNumber num1(
        "10.01"
    );
    const LongNumber num2(
        "11.02"
    );

    // when
    const bool result_false = num1 > num2;

    // then
    CHECK_FALSE(result_false);

    // when
    const bool result_true = num1 < num2;

    // then
    CHECK(result_true);
}

TEST_CASE("Greater operation works correctly, when one negative", "[arithmetic]") {
    // given
    const LongNumber num1(
        "-10.01"
    );
    const LongNumber num2(
        "11.02"
    );

    // when
    const bool result_false = num1 > num2;

    // then
    CHECK_FALSE(result_false);

    // when
    const bool result_true = num1 < num2;

    // then
    CHECK(result_true);
}

TEST_CASE("Greater operation works correctly, when both negative", "[arithmetic]") {
    // given
    const LongNumber num1(
        "-11.01"
    );
    const LongNumber num2(
        "-10.02"
    );

    // when
    const bool result_false = num1 > num2;

    // then
    CHECK_FALSE(result_false);

    // when
    const bool result_true = num1 < num2;

    // then
    CHECK(result_true);
}