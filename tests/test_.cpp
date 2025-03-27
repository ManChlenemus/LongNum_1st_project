#include <catch2/catch_test_macros.hpp>
#include "longnum.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"
typedef LongNum LongNumber;

TEST_CASE("Plus operation works correctly, when both positive and no fractional part", "[arithmetic]") {
    // given
    const LongNumber num1("10");
    const LongNumber num2("10");

    // when
    const LongNumber result = num1 + num2;

    // then
    const LongNumber expected("20");
    REQUIRE(result == expected);
}

TEST_CASE("Plus operation works correctly, when both positive and no integer part", "[arithmetic]") {
    // given
    const LongNumber num1("0.50");
    const LongNumber num2("0.75");

    // when
    const LongNumber result = num1 + num2;

    // then
    const LongNumber expected("1.25", 16);
    REQUIRE(result == expected);
}

TEST_CASE("Plus operation works correctly, when both positive", "[arithmetic]") {
    // given
    const LongNumber num1("10.5");
    const LongNumber num2("10.75");

    // when
    const LongNumber result = num1 + num2;

    // then
    const LongNumber expected("21.25");
    REQUIRE(result == expected);
}

TEST_CASE("Plus operation works correctly, when one negative", "[arithmetic]") {
    // given
    const LongNumber num1("-10.75");
    const LongNumber num2("10.75");

    // when
    const LongNumber result = num1 + num2;

    // then
    const LongNumber expected("0");
    REQUIRE(result == expected);
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
    REQUIRE(result == expected);
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
    REQUIRE(result_negative == expected_negative);
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
    REQUIRE(result == expected);
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
    REQUIRE(result == expected);
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
    REQUIRE(result == expected);
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
    REQUIRE(result == expected);
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
    REQUIRE(result == expected);
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
    REQUIRE(result == expected);
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
    REQUIRE(result_true);
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
    REQUIRE(result_true);
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
    REQUIRE(result_true);
}

LongNumber calculate_pi(int precision) {
    long long bob = 0;
    if(precision > 50){
        bob = precision * 3.4;
    } else {
        bob = precision * 4;
    }
    LongNumber pi("0.0", bob);
    LongNumber sixteen("16.0", bob);
    LongNumber sixteen_pow("1.0", bob);
    LongNumber one("1.0", bob);
    LongNumber two ("2.0", bob);
    LongNumber four ("4.0", bob);
    LongNumber five ("5.0", bob);
    LongNumber six ("6.0", bob);
    LongNumber eight("8.0", bob);

    for (int k = 0; k < precision; ++k) {

        LongNumber term1 = four / ((eight * LongNumber(k, bob)) + one);
        LongNumber term2 = two / ((eight * LongNumber(k, bob)) + four);
        LongNumber term3 = one / ((eight * LongNumber(k, bob)) + five);
        LongNumber term4 = one / ((eight * LongNumber(k, bob)) + six);
        LongNumber term = ((((term1 - term2) - term3) - term4)) / sixteen_pow;
        if(k != precision - 1){
            sixteen_pow = sixteen_pow * sixteen;
        }
        pi = pi + term;
    }
    return pi;
}

TEST_CASE("Calculate pi result", "[benchmark]") {
    auto pi = calculate_pi(100);
    pi.print_dec(100);
    std::cout << "For compare: 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679" << std::endl;

}

TEST_CASE("Calculate pi banchmark", "[benchmark]") {
    BENCHMARK("pi100") {
        return calculate_pi(100);
    };
}

