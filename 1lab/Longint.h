#pragma once
#ifndef LongInt_H
#define LongInt_H
#include <string>

class LongInt {
private:
    std::string longNum;
    bool isPos;
    std::string add_string_to_string(const LongInt& other);
    std::string sub_string_from_string(const LongInt& other);
    std::string multiply_strings(const LongInt& other);
    std::string longDivision(const LongInt& other);
    void removeOperationPlus_setMinus(LongInt first, LongInt other);
    void subTwoPositive(const LongInt& other);
    void subTwoNegative(const LongInt& other);

    LongInt addLong(const LongInt& other);
    LongInt subLong(const LongInt& other);
    LongInt multlong(const LongInt& other);
    LongInt divLong(const LongInt& other);

    LongInt addInt(const int& other);
    LongInt subInt(const int& other);
    LongInt multInt(const int& other);
    LongInt divInt(const int& other);

public:
    LongInt() {};
    LongInt(const std::string& str);
    int to_integer(){};
    int size();
    void setLong(const std::string&str);
    std::string getLong();

    LongInt operator+(const LongInt& other);
    LongInt operator-(const LongInt& other);
    LongInt operator*(const LongInt& other);
    LongInt operator/(const LongInt& other);
    LongInt operator+=(const LongInt& other);
    LongInt operator-=(const LongInt& other);
    LongInt operator*=(const LongInt& other);
    LongInt operator/=(const LongInt& other);


    LongInt operator+(const int& other);
    LongInt operator-(const int& other);
    LongInt operator*(const int& other);
    LongInt operator/(const int& other);
    LongInt operator+=(const int& other);
    LongInt operator-=(const int& other);
    LongInt operator*=(const int& other);
    LongInt operator/=(const int& other);
   
    LongInt operator++(int);
    LongInt operator++();
    LongInt operator--(int);
    LongInt operator--();
    bool operator<=(const LongInt& other);
    bool operator<(const LongInt& other);
    bool operator>=(const LongInt& other);
    bool operator>(const LongInt& other);
    bool operator<=(const int& intOther);
    bool operator<(const int& intOther);
    bool operator>=(const int& intOther);
    bool operator>(const int& intOther);
};
#endif // !LongInt

