#pragma once
#ifndef LONGINT_H
#define LONGINT_H
#include <string>

class Longint {
private:
    std::string longNum;
    bool isPos;
    std::string add_string_to_string(const Longint& other);
    std::string sub_string_from_string(const Longint& other);
    std::string multiply_strings(const Longint& other);
    std::string longDivision(const Longint& other);
    void removeOperationPlus_setMinus(Longint first, Longint other);
    void subTwoPositive(const Longint& other);
    void subTwoNegative(const Longint& other);

    Longint addLong(const Longint& other);
    Longint subLong(const Longint& other);
    Longint multlong(const Longint& other);
    Longint divLong(const Longint& other);

    Longint addInt(const int& other);
    Longint subInt(const int& other);
    Longint multInt(const int& other);
    Longint divInt(const int& other);

public:
    Longint() {};
    Longint(const std::string& str);
    int to_integer(){};
    int size();
    void setLong(const std::string&str);
    std::string getLong();

    Longint operator+(const Longint& other);
    Longint operator-(const Longint& other);
    Longint operator*(const Longint& other);
    Longint operator/(const Longint& other);
    Longint operator+=(const Longint& other);
    Longint operator-=(const Longint& other);
    Longint operator*=(const Longint& other);
    Longint operator/=(const Longint& other);


    Longint operator+(const int& other);
    Longint operator-(const int& other);
    Longint operator*(const int& other);
    Longint operator/(const int& other);
    Longint operator+=(const int& other);
    Longint operator-=(const int& other);
    Longint operator*=(const int& other);
    Longint operator/=(const int& other);
   
    Longint operator++(int);
    Longint operator++();
    Longint operator--(int);
    Longint operator--();
    bool operator<=(const Longint& other);
    bool operator<(const Longint& other);
    bool operator>=(const Longint& other);
    bool operator>(const Longint& other);
    bool operator<=(const int& intOther);
    bool operator<(const int& intOther);
    bool operator>=(const int& intOther);
    bool operator>(const int& intOther);
};
#endif // !LONGINT

