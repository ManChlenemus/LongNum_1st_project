#include "longnum.h"
#include <cmath>
#include <iostream>
#include <ostream>

#include <vector>
#include <algorithm>
#include <iterator>
#include <bits/locale_facets_nonio.h>

LongNum::LongNum() : precision_frac(0), precision_int(1) {
    int_part.push_back(0);
}

LongNum::LongNum(const LongNum &num) : sign(num.sign),
                                       precision_frac(num.precision_frac),
                                       precision_int(num.precision_int) {
    for (int element: num.int_part) {
        int_part.push_back(element);
    }
    for (int element: num.frac_part) {
        frac_part.push_back(element);
    }
}

LongNum &LongNum::operator=(const LongNum &num) {
    // Удаление прошлого
    size_t size = int_part.size();
    for (size_t i = 0; i < size; i++) {
        int_part.pop_back();
    }
    size = frac_part.size();
    for (size_t i = 0; i < size; i++) {
        frac_part.pop_back();
    }

    // Копирование
    sign = num.sign;
    precision_frac = num.precision_frac;
    precision_int = num.precision_int;

    for (int element: num.int_part) {
        int_part.push_back(element);
    }
    for (int element: num.frac_part) {
        frac_part.push_back(element);
    }
    return *this;
}

int cmp_long_num(const LongNum &first, const LongNum &second) {
    if (first.precision_int == second.precision_int) {
        // Сравним целые части
        for (long long i = first.precision_int - 1; i >= 0; i--) {
            if (first.int_part[i] != second.int_part[i]) {
                return first.int_part[i] > second.int_part[i] ? 1 : -1;
            }
        }
        // Целые равны => сравним дробные
        if (first.precision_frac == second.precision_frac) {
            for (long long i = 0; i < first.precision_frac; i++) {
                if (first.frac_part[i] != second.frac_part[i]) {
                    return first.frac_part[i] > second.frac_part[i] ? 1 : -1;
                }
            }
            // Если и дробные равны => равенство
            return 0;
        }
        // Если дробные части отличаются по точности
        if (first.precision_frac * second.precision_frac) {
            if (first.precision_frac > second.precision_frac) {
                // Первое "длиннее"
                for (long long i = 0; i < second.precision_frac; i++) {
                    if (first.frac_part[i] != second.frac_part[i]) {
                        return first.frac_part[i] > second.frac_part[i] ? 1 : -1;
                    }
                }
                return 1;
            } else {
                // Второе "длиннее"
                for (long long i = 0; i < first.precision_frac; i++) {
                    if (first.frac_part[i] != second.frac_part[i]) {
                        return first.frac_part[i] > second.frac_part[i] ? 1 : -1;
                    }
                }
            }
            return -1;
        } else {
            return first.precision_frac == 0 ? -1 : 1;
        }

    }
    return first.precision_int > second.precision_int ? 1 : -1;
}

void LongNum::StrToBin(std::string s, long long point) {
    // Если нам подали целое число
    if (point == -1) {
        precision_frac = 0;
        // Переводим str->vector
        std::vector<int> decimal_bits;
        long long size_int = s.length();
        for (int i = 0; i < size_int; i++) {
            decimal_bits.push_back(s[i] - '0');
        }
        // Теперь перевод в бинарный вид
        std::vector<int> res_int;
        long long size_int_temp = size_int;
        int cnt = 0; // Счетчик бинарных разрядов (для точности)
        while (size_int_temp > 0 && cnt < precision_int) {
            // Остаток младшего байта = значение очередного бин. разряда
            res_int.push_back(decimal_bits[size_int - 1] % 2);
            decimal_bits[size_int - 1] /= 2;

            int remainder = 0; // Остаток
            for (long long i = size_int - 2; i >= 0; i--) {
                remainder = decimal_bits[i] % 2;
                decimal_bits[i] = decimal_bits[i] / 2;

                // Если есть остаток (rem. = 1), то прошлый разряд +5
                if (remainder == 1) {
                    decimal_bits[i + 1] += 5;
                }
            }
            // Если старший разряд был 1 (в последствии стал 0), размер уменьшается
            if (decimal_bits[size_int - size_int_temp] == 0) {
                size_int_temp--;
            }
            cnt++; // количество знаков двоичной записи
        }
        int_part = std::move(res_int);
        return;
    }

    // Если нам подали дробное число
    long long len = s.length();
    // Разделение на целую и дробную части
    std::string s_int = s.substr(0, point);
    std::string s_frac = s.substr(point + 1, len - 1);

    // Сначала переведем целую часть (s_int)
    std::vector<int> decimal_bits; // Вектор битов целой части
    // Соответственно перевод str->vector
    long long size_int = s_int.length();
    for (long long i = 0; i < size_int; i++) {
        decimal_bits.push_back(s_int[i] - '0');
    }

    // Теперь перевод decimal->binary (целая часть)
    std::vector<int> res_int;
    long long size_int_temp = size_int;
    int cnt = 0; // Счетчик бинарных разрядов (для точности)
    while (size_int_temp > 0 && cnt < precision_int) {
        // Остаток младшего байта = значение очередного бин. разряда
        res_int.push_back(decimal_bits[size_int - 1] % 2);
        decimal_bits[size_int - 1] /= 2;

        int remainder = 0; // Остаток
        for (long long i = size_int - 2; i >= 0; i--) {
            remainder = decimal_bits[i] % 2;
            decimal_bits[i] = decimal_bits[i] / 2;

            // Если есть остаток (rem. = 1), то прошлый разряд +5
            if (remainder == 1) {
                decimal_bits[i + 1] += 5;
            }
        }
        // Если старший разряд был 1 (в последствии стал 0), размер уменьшается
        if (decimal_bits[size_int - size_int_temp] == 0) {
            size_int_temp--;
        }
        cnt++; // количество знаков двоичной записи
    }

    // Аналогично переведем дробную часть (s_frac)
    std::vector<int> fractional_bits; // Вектор битов дробной части
    // Соответственно перевод str->vector
    fractional_bits.push_back(0); // !! Тк мы умножаем, то добавим 0 в первый слот
    long long size_frac = s_frac.length();
    for (long long i = 0; i < size_frac; i++) {
        fractional_bits.push_back(s_frac[i] - '0');
    }

    // Теперь перевод decimal->binary (дробная часть)
    std::vector<int> res_frac;
    long long size_frac_temp = size_frac + 1; // +1 тк в начало мы добавили вспомогательный 0
    cnt = 0; // Обнуляем счетчик (теперь он для дробной точности)
    while (size_frac_temp > 1 && cnt < precision_frac) {
        int overage = 0; // Избыток значения (7 * 2 = 14 {1 - это overage} )

        for (long long i = size_frac_temp - 1; i >= 0; i--) {
            fractional_bits[i] *= 2;
            // Если есть избыток при умножении
            if (overage) {
                fractional_bits[i] += overage;
            }
            overage = fractional_bits[i] / 10;
            fractional_bits[i] = fractional_bits[i] % 10;
        }
        res_frac.push_back(fractional_bits[0]);
        // Очищаем нулевую (буфферную) ячейку
        fractional_bits[0] = 0;
        // Если последний разряд стал нулем уменьшим размер
        if (fractional_bits[size_frac_temp - 1] == 0) {
            size_frac_temp--;
        }
        cnt++;
    }
    while (res_frac[res_frac.size() - 1] == 0) {
        res_frac.pop_back();
    }
    int_part = std::move(res_int);
    frac_part = std::move(res_frac);
}

LongNum::LongNum(std::string s, int prec_frac, int prec_int)
    : precision_int(prec_int), precision_frac(prec_frac) {
    long long len = s.length();
    // Проверка на отрицательность
    if (s[0] == '-') {
        sign = -1;
        s = s.substr(1, len - 1);
        len--;
    }
    // Нахождение точки
    long long point = -1;
    for (long long i = 0; i < len; i++)
        if (s[i] == '.') point = i;

    StrToBin(s, point);
    precision_frac = frac_part.size();
    precision_int = int_part.size();
}

LongNum::LongNum(long double num, int prec_frac, int prec_int)
    : precision_int(prec_int), precision_frac(prec_frac) {
    std::string s = std::to_string(num);
    // Если бы была возможность использовать конструктор в конструктре... Эх

    long long len = s.length();
    // Проверка на отрицательность
    if (s[0] == '-') {
        sign = -1;
        s = s.substr(1, len - 1);
        len--;
    }
    // Нахождение точки
    long long point = -1;
    for (long long i = 0; i < len; i++)
        if (s[i] == '.') point = i;

    StrToBin(s, point);
    precision_frac = frac_part.size();
    precision_int = int_part.size();
}

LongNum LongNum::operator+(const LongNum &other) const {
    LongNum result(0);
    long long max_int_len = std::max(this->precision_int, other.precision_int);
    long long min_int_len = std::min(this->precision_int, other.precision_int);
    long long max_frac_len = std::max(this->precision_frac, other.precision_frac);
    long long min_frac_len = std::min(this->precision_frac, other.precision_frac);
    result.precision_int = max_int_len;
    result.precision_frac = max_frac_len;
    // Если числа одного знака
    if (this->sign * other.sign == 1) {
        result.sign = this->sign;
        int overage = 0; // избыток по сложению

        // Сначала дробная часть
        if (max_frac_len != 0) {
            std::vector<int> tmp(max_frac_len, 0);
            for (long long i = min_frac_len; i < max_frac_len; i++) {
                tmp[i] = this->precision_frac > other.precision_frac
                             ? this->frac_part[i]
                             : other.frac_part[i];
            }
            for (long long i = min_frac_len - 1; i >= 0; i--) {
                tmp[i] = this->frac_part[i] + other.frac_part[i] + overage;
                overage = tmp[i] / 2;
                tmp[i] = tmp[i] % 2;
            }
            result.frac_part = std::move(tmp);
        }


        // Теперь целая часть
        result.int_part[0] = overage;
        for (long long i = 0; i < min_int_len; i++) {
            overage = 0;
            int i_res = this->int_part[i] + other.int_part[i] + result.int_part[i];
            overage = i_res / 2;
            i_res = i_res % 2;
            result.int_part[i] = i_res;
            if (i != min_int_len - 1) {
                result.int_part.push_back(overage);
            }
        }
        // Дозаполняем число "излишками"
        for (long long i = min_int_len; i < max_int_len; i++) {
            result.int_part.push_back(this->precision_int > other.precision_int
                                          ? this->int_part[i]
                                          : other.int_part[i]);
        }
        // Добавим оставшийся overage
        int it = 0;
        while (overage) {
            if (it + min_int_len >= max_int_len) result.int_part.push_back(0);
            result.int_part[it + min_int_len] += overage;
            overage = result.int_part[it + min_int_len] / 2;
            result.int_part[it + min_int_len] %= 2;
            it++;
        }
    }
    // Если мы складываем числа разных знаков (вычитаем)
    else {
        LongNum *big_ptr;
        LongNum *small_ptr;
        const LongNum *longer_ptr = this->precision_frac > other.precision_frac ? this : &other;
        const LongNum *smaller_ptr = this->precision_frac > other.precision_frac ? &other : this;
        if (cmp_long_num(*this, other) == 1) {
            big_ptr = const_cast<LongNum *>(this);
            small_ptr = const_cast<LongNum *>(&other);
            if (this->sign == -1) result.sign = -1;
            else result.sign = 1;
        } else {
            big_ptr = const_cast<LongNum *>(&other);
            small_ptr = const_cast<LongNum *>(this);
            if (this->sign == -1) result.sign = 1;
            else result.sign = -1;
        }
        // Сначала дробная часть
        if (max_frac_len != 0) {
            // Если длины равны
            if (max_frac_len == min_frac_len) {
                result.frac_part = big_ptr->frac_part;
                for (long long i = min_frac_len - 1; i >= 1; i--) {
                    if (result.frac_part[i + 1] < 0 && (i != min_frac_len - 1)) {
                        result.frac_part[i]--;
                        result.frac_part[i + 1] += 2;
                    }
                    result.frac_part[i] -= small_ptr->frac_part[i];
                }
                // Обработка переходного случая (через точку)
                // Длины равны и макс_длина != 0, поэтому всегда выполняется
                result.frac_part[0] -= small_ptr->frac_part[0];
                if (result.frac_part[0] < 0) {
                    result.frac_part[0] += 2;
                    result.int_part[0]--;
                }
            }
            // Если длины не равны
            else {
                // 1 случай (когда длины не равны)
                if (longer_ptr == big_ptr) {
                    for (long long i = 0; i < min_frac_len; i++) {
                        result.frac_part.push_back(0);
                    }
                    for (long long i = min_frac_len; i < max_frac_len; i++) {
                        result.frac_part.push_back(big_ptr->frac_part[i]);
                    }
                    for (long long i = min_frac_len - 1; i >= 1; i--) {
                        if (result.frac_part[i + 1] < 0) {
                            result.frac_part[i]--;
                            result.frac_part[i + 1] += 2;
                        }
                        result.frac_part[i] += big_ptr->frac_part[i] - small_ptr->frac_part[i];
                    }
                    // Обработка переходного случая (через точку)
                    if (min_frac_len > 0) {
                        if (max_frac_len > 1) {
                            if (result.frac_part[1] < 0) {
                                result.frac_part[1] += 2;
                                result.frac_part[0]--;
                            }
                        }
                        result.frac_part[0] += big_ptr->frac_part[0] - small_ptr->frac_part[0];
                        if (result.frac_part[0] < 0) {
                            result.frac_part[0] += 2;
                            result.int_part[0]--;
                        }
                    } // Случай, когда короткое (по длине) число не имеет дробной части, рассматривать не надо (стр 318-319)
                } else { // longer != bigger (= smaller)
                    for (long long i = 0; i < max_frac_len; i++) {
                        result.frac_part.push_back(0);
                    }
                    for (long long i = max_frac_len - 1; i > min_frac_len - 1; i--) {
                        if (result.frac_part[i + 1] < 0 && i != max_frac_len - 1) {
                            result.frac_part[i]--;
                            result.frac_part[i + 1] += 2;
                        }
                        result.frac_part[i] -= small_ptr->frac_part[i];
                    }
                    for (long long i = min_frac_len - 1; i >= 1; i--) {
                        if (result.frac_part[i + 1] < 0) {
                            result.frac_part[i]--;
                            result.frac_part[i + 1] += 2;
                        }
                        result.frac_part[i] += big_ptr->frac_part[i] - small_ptr->frac_part[i];
                    }
                    // Обработка переходного случая (через точку)
                    if (min_frac_len > 0) {
                        if (max_frac_len > 1) {
                            if (result.frac_part[1] < 0) {
                                result.frac_part[1] += 2;
                                result.frac_part[0]--;
                            }
                        }
                        result.frac_part[0] += big_ptr->frac_part[0] - small_ptr->frac_part[0];
                    } else {
                        result.frac_part[0] -= small_ptr->frac_part[0];
                    }

                    if (result.frac_part[0] < 0) {
                        result.frac_part[0] += 2;
                        result.int_part[0]--;
                    }
                }
            }
        }

        // Целая часть (вычитание)
        result.int_part[0] += big_ptr->int_part[0] - small_ptr->int_part[0];
        for (long long i = 1; i < min_int_len; i++) {
            result.int_part.push_back(big_ptr->int_part[i] - small_ptr->int_part[i]);
            if (result.int_part[i - 1] < 0) {
                result.int_part[i - 1] += 2;
                result.int_part[i]--;
            }
        }
        for (long long i = min_int_len; i < max_int_len; i++) {
            result.int_part.push_back(big_ptr->int_part[i]);
            if (result.int_part[i - 1] < 0) {
                result.int_part[i - 1] += 2;
                result.int_part[i]--;
            }
        }
    }
    while (result.frac_part[result.frac_part.size() - 1] == 0) {
        result.frac_part.pop_back();
    }
    while (result.int_part[result.int_part.size() - 1] == 0 && result.int_part.size() > 1) {
        result.int_part.pop_back();
    }
    result.precision_frac = result.frac_part.size();
    result.precision_int = result.int_part.size();
    if (result.precision_frac == 0 && result.precision_int == 1 && result.int_part[0] == 0) result.sign = 1;
    return result;
}

LongNum LongNum::operator-() const {
    LongNum result = *this;
    result.sign *= -1;
    return result;
}

LongNum LongNum::operator-(const LongNum &other) const {
    return (*this) + (-other);
}

bool LongNum::operator==(const LongNum &other) const{
    if (other.sign != this->sign) return false;
    if (other.precision_frac != this->precision_frac) return false;
    if (other.precision_int != this->precision_int) return false;

    for (long long i = 0; i < this->int_part.size(); i++)
        if (this->int_part[i] != other.int_part[i]) return false;
    for (long long i = 0; i < this->frac_part.size(); i++)
        if (this->frac_part[i] != other.frac_part[i]) return false;
    return true;
}


bool LongNum::operator!=(const LongNum &other) const {
    return !(*this == other);
}

bool LongNum::operator<(const LongNum &other) const {
    LongNum res = *this - other;
    if (res.sign == -1) return true;
    return false;
}

bool LongNum::operator<=(const LongNum &other) const {
    return *this < other || *this == other;
}

bool LongNum::operator>(const LongNum &other) const {
    LongNum res = *this - other;
    if (*this != other && res.sign == 1) return true;
    return false;
}

bool LongNum::operator>=(const LongNum &other) const {
    return *this > other || *this == other;
}

LongNum LongNum::operator*(const LongNum &other) const {
    std::vector<int> first;
    std::vector<int> second;

    // Выделим место
    first.reserve(this->int_part.size() + this->frac_part.size());
    second.reserve(other.int_part.size() + other.frac_part.size());

    // Создаем итоговый вектор
    std::vector<int> result(this->int_part.size() + this->frac_part.size() +
        other.int_part.size() + other.frac_part.size());

    // Соединим векторы (this) в первый
    for (long long i = this->frac_part.size() - 1; i >= 0; i--) {
        first.push_back(this->frac_part[i]);
    }
    first.insert(first.end(), this->int_part.begin(), this->int_part.end());

    // Соединим векторы (other) во второй
    for (long long i = other.frac_part.size() - 1; i >= 0; i--) {
        second.push_back(other.frac_part[i]);
    }
    second.insert(second.end(), other.int_part.begin(), other.int_part.end());

    int carry = 0;
    // Теперь этап умножения
    for (long long i = 0; i < first.size(); i++) {
        for (long long j = 0; j < second.size(); j++) {
            int product = first[i] * second[j];
            result[i + j] += product % 2 + carry;
            carry = product / 2;
        }
    }
    // Просеивание влево
    for (long long i = 0; i < result.size(); i++) {
        while (result[i] > 1) {
            result[i] -= 2;
            result[i + 1]++;
        }
    }
    // Создадим return-вектор
    LongNum tmp;
    tmp.precision_frac = this->precision_frac + other.precision_frac;
    tmp.precision_int = this->precision_int + other.precision_int;
    tmp.sign = this->sign * other.sign;
    for (long long i = 0; i < tmp.precision_frac; i++) {
        tmp.frac_part.push_back(result[(result.size() - 1) - tmp.precision_int - i]);
    }
    // Инициализируем его int и frac части путем копирования
    tmp.int_part[0] = result[tmp.precision_frac]; // Обработка отдельного случая (тк у нас уже есть 0 в int части)
    for (long long i = tmp.precision_frac + 1; i < tmp.precision_int + tmp.precision_frac; i++) {
        tmp.int_part.push_back(result[i]);
    }
    // На всякий случай сделаем проверку на незначащие нули в записи
    while (tmp.int_part[tmp.int_part.size() - 1] == 0 && tmp.int_part.size() > 1)
        tmp.int_part.pop_back();
    if (!tmp.frac_part.empty())
        while (tmp.frac_part[tmp.frac_part.size() - 1] == 0)
            tmp.frac_part.pop_back();
    tmp.precision_frac = tmp.frac_part.size();
    tmp.precision_int = tmp.int_part.size();
    return tmp;
}

LongNum LongNum::operator/(const LongNum &other) const {
    // Проверка деления на ноль
    if (other.precision_int == 1 && other.precision_frac == 0 &&
        other.int_part[0] == 0) {
        std::cout << "Division by zero" << std::endl;
        return 0.0_longnum;
    }

    // Создаем копии делимого и делителя без учета знака
    LongNum dividend = *this;
    dividend.sign = 1;
    LongNum divisor = other;
    divisor.sign = 1;

    // Инициализация результата
    LongNum result;
    result.sign = this->sign * other.sign;

    // Приведение делителя к целому числу
    for (long long i = 0; i < divisor.frac_part.size(); i++) {
        if (dividend.frac_part.size() > 0) {
            dividend.int_part.insert(dividend.int_part.begin(), dividend.frac_part[0]);
            dividend.frac_part.erase(dividend.frac_part.begin());
        } else {
            dividend.int_part.insert(dividend.int_part.begin(), 0);
        }

        divisor.int_part.insert(divisor.int_part.begin(), divisor.frac_part[0]);
        divisor.frac_part.erase(divisor.frac_part.begin());
    }

    // Удаление незначащих нулей
    // divisor
    while (divisor.int_part.size() > 1 && divisor.int_part.back() == 0) {
        divisor.int_part.pop_back();
    }
    while (!(divisor.frac_part.empty()) && divisor.frac_part.back() == 0) {
        divisor.frac_part.pop_back();
    }
    divisor.precision_int = divisor.int_part.size();
    divisor.precision_frac = divisor.frac_part.size();
    // dividend
    while (dividend.int_part.size() > 1 && dividend.int_part.back() == 0) {
        dividend.int_part.pop_back();
    }
    while (!(dividend.frac_part.empty()) && dividend.frac_part.back() == 0) {
        dividend.frac_part.pop_back();
    }
    dividend.precision_int = dividend.int_part.size();
    dividend.precision_frac = dividend.frac_part.size();

    // Инициализация промежуточного остатка
    LongNum remainder;
    remainder.int_part.pop_back();
    remainder.precision_int = 0;
    // Деление целой части
    for (size_t i = 0; i < dividend.int_part.size(); i++) {
        if (!(dividend.int_part[dividend.int_part.size() - 1 - i] == 0 && remainder == 0.0_longnum)) {
            remainder.int_part.insert(remainder.int_part.begin(),
                dividend.int_part[dividend.int_part.size() - 1 - i]);
            while (remainder.int_part.back() == 0) remainder.int_part.pop_back();
            remainder.precision_int = remainder.int_part.size(); // важно для сравнения
        }
        if (remainder >= divisor) {
            remainder = remainder - divisor;
            result.int_part.insert(result.int_part.begin(), 1); // результат потом реверснуть
        } else
            result.int_part.insert(result.int_part.begin(), 0);
    }


    while (remainder.int_part.back() == 0) {
        remainder.int_part.pop_back();
    }
    remainder.precision_int = remainder.int_part.size();

    // Деление дробной части
    size_t i;
    for (i = 0; i < dividend.frac_part.size(); i++) {
        if (!(remainder == 0.0_longnum && dividend.frac_part[i] == 0)) {
            remainder.int_part.insert(remainder.int_part.begin(), dividend.frac_part[i]);
            while (remainder.int_part.back() == 0) remainder.int_part.pop_back();
            remainder.precision_int = remainder.int_part.size(); // важно для сравнения
        }
        if (remainder >= divisor) {
            remainder = remainder - divisor;
            result.frac_part.push_back(1);
        } else {
            result.frac_part.push_back(0);
        }
    }
    // Если число закончилось добавляем нули
    while (i < 300 && remainder != 0.0_longnum) {
        remainder.int_part.insert(remainder.int_part.begin(), 0);
        remainder.precision_int = remainder.int_part.size(); // важно для сравнения
        if (remainder >= divisor) {
            remainder = remainder - divisor;
            result.frac_part.push_back(1);
        } else {
            result.frac_part.push_back(0);
        }
        i++;
    }

    // Удаление незначащих нулей
    while (result.int_part.size() > 1 && result.int_part.back() == 0) {
        result.int_part.pop_back();
    }
    while (!(result.frac_part.empty()) && result.frac_part.back() == 0) {
        result.frac_part.pop_back();
    }
    result.precision_int = result.int_part.size();
    result.precision_frac = result.frac_part.size();
    return result;
}

LongNum operator""_longnum(long double num) {
    LongNum res(num);
    return res;
}

bool LongNum::isNull() const {
    LongNum EPS("0.00000000001");
    if (*this < EPS && *this > -EPS || *this == 0.0_longnum) return true;
    return false;
}


void LongNum::print_ln() {
    std::cout << "Bin_num: ";
    if (sign == -1) std::cout << "-";
    for (auto element = int_part.rbegin(); element != int_part.rend(); element++) {
        std::cout << (*element);
    }
    if (precision_frac != 0) {
        std::cout << ".";
        for (int element: frac_part) {
            std::cout << element;
        }
    }
    std::cout << std::endl;

    std::cout << "[pr_int = " << precision_int << "] [pr_frac = " << precision_frac << "]" << std::endl;
}

void LongNum::print_dec(long long precision_fraction, long long precision_integer) {
    std::cout << "Dec_num: ";
    if (sign == -1) std::cout << "-";
    std::string int_num;
    std::string fract_num;

    for (int element: int_part) {
        int_num += std::to_string(element);
    }
    for (int element: frac_part) {
        fract_num += std::to_string(element);
    }
    std::reverse(int_num.begin(), int_num.end());
    std::reverse(fract_num.begin(), fract_num.end());

    std::string int_res = "0"; // Начинаем с нуля (инициализация)
    std::string fract_res = "0";
    // -------------------------------------------------- Целая часть --------------------------------------------------
    // обрабатываем каждый бит
    for (char bit: int_num) {
        // Умножаем текущее десятичное число на 2
        int carry = 0;
        for (char &digit: int_res) {
            int product = (digit - '0') * 2 + carry;
            digit = (product % 10) + '0';
            carry = product / 10;
        }
        if (carry > 0) {
            int_res.push_back(carry + '0');
        }

        // Добавляем текущий бит
        if (bit == '1') {
            int sumCarry = 1;
            for (char &digit: int_res) {
                int sum = (digit - '0') + sumCarry;
                digit = (sum % 10) + '0';
                sumCarry = sum / 10;
                if (sumCarry == 0) break;
            }
            if (sumCarry > 0) {
                int_res.push_back(sumCarry + '0');
            }
        }
    }
    // ------------------------------------------------- Дробная часть -------------------------------------------------
    // Обрабатываем каждый бит
    for (char bit: fract_num) {
        // Добавляем текущий бит
        if (bit == '1') {
            fract_res[fract_res.length()-1] = '1';
        }

        // Делим число на 2 (умножаем и двигаем точку)
        int carry = 0;
        for (char &digit: fract_res) {
            int product = (digit - '0') * 5 + carry;
            digit = (product % 10) + '0';
            carry = product / 10;
        }
        fract_res.push_back(carry + '0'); // перенос запятой (если carry = 0)
    }
    fract_res.pop_back(); // Так как изначально мы не считаем 0.5 как 5 => мы делаем лишний перенос

    // Переворачиваем строку и выводим результат
    std::reverse(int_res.begin(), int_res.end());
    std::reverse(fract_res.begin(), fract_res.end());

    // Округление
    if (precision_fraction < fract_res.size()) {
        if ('5' <= fract_res[precision_fraction] && fract_res[precision_fraction] <= '9')
            if (fract_res[precision_fraction - 1] != '9') // чтобы не залезть в рекурсию (выборочное округление)
                fract_res[precision_fraction - 1] += 1;
        fract_res = fract_res.substr(0, precision_fraction);
    }

    std::cout << int_res;
    if (precision_frac != 0) std::cout << "." << fract_res;
    std::cout << std::endl;
}
