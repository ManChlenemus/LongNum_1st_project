#ifndef LONGNUM_H
#define LONGNUM_H

#include <vector>
#include <string>
#include <iostream>
#include <cstdint>

class LongNum {
public:
    int8_t sign = 1;
    std::vector<int> int_part;
    std::vector<int> frac_part;
    long long precision_int; // роль точности и размера целочисленной части
    long long precision_frac; // роль точности и размера дробной части

// public: // Конструкторы + операторы
    LongNum();

    explicit LongNum(long double num, int prec_frac = 100, int prec_int = 100);

    explicit LongNum(std::string s, int prec_frac = 100, int prec_int = 100);

    LongNum(const LongNum &num); // Конструктор копирования

    LongNum &operator=(const LongNum &other);


    // Классические (арифметические) операторы
    LongNum operator+(const LongNum& other) const;

    LongNum operator-() const;

    LongNum operator-(const LongNum &other) const;

    LongNum operator*(const LongNum &other) const;

    LongNum operator/(const LongNum &other) const;

    // Логические (булевые) операторы
    bool operator==(const LongNum &other) const;

    bool operator!=(const LongNum &other) const;

    bool operator<(const LongNum &other) const;

    bool operator>(const LongNum &other) const;

    // Для удобства
    bool operator<=(const LongNum &other) const;

    bool operator>=(const LongNum &other) const;

    // Методы
    bool isNull() const;
    void StrToBin(std::string s, long long point);
    void print_ln(); // print_long_num
    void print_dec(long long precision_fraction = 100, long long precision_integer = 100); // print_decimal
    friend int cmp_long_num(const LongNum &first, const LongNum &second);

};

LongNum operator""_longnum(long double num);


#endif //LONGNUM_H