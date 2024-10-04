
#include "D:/LABY/BSUIR/1labaPPOIS/Longint.h"
#include <iostream>
#include <string>
#include <algorithm>
const int MAX_INT = 2147483647;
const int MIN_INT = -2147483647;

std::string Longint::add_string_to_string(const Longint& other)
{
    std::string sumResult;
    int v_ume = 0;
    int maxLength = std::max(int(longNum.size()), int(other.longNum.size()));
    for (int i = 0; i < maxLength; ++i)
    {
        int digitLeft = (i < longNum.size()) ? (longNum[longNum.size() - 1 - i] - '0') : 0;
        int digitRight = (i < other.longNum.size()) ? (other.longNum[other.longNum.size() - 1 - i] - '0') : 0;
        int sum = digitLeft + digitRight + v_ume;
        v_ume = sum / 10;
        sumResult += std::to_string(sum % 10);
    }
    if (v_ume > 0)
    {
        sumResult += std::to_string(v_ume);
    }
    std::reverse(sumResult.begin(), sumResult.end());
    return sumResult;
}
std::string Longint::sub_string_from_string(const Longint& other)
{
    std::string diffResult;
    int v_ume = 0;
    int maxLength = std::max(int(longNum.size()), int(other.longNum.size()));
    for (int i = 0; i < maxLength; ++i)
    {
        int digitLeft = (i < longNum.size()) ? (longNum[longNum.size() - 1 - i] - '0') : 0;
        int digitRight = (i < other.longNum.size()) ? (other.longNum[other.longNum.size() - 1 - i] - '0') : 0;
        int diff = digitLeft - digitRight - v_ume;
        v_ume = (diff < 0) ? 1 : 0;
        diffResult += std::to_string((diff + 10) % 10);
    }
    if (isPos)
    {
        while (diffResult.size() > 1 && diffResult.back() == '0')
        {
            diffResult.pop_back();
        }
    }
    std::reverse(diffResult.begin(), diffResult.end());

    return diffResult;
}
std::string Longint::multiply_strings(const Longint& other)
{
    Longint result;
    for (int i = 0; i < other.longNum.size(); ++i)
    {
        int digitRight = other.longNum[other.longNum.size() - 1 - i] - '0';
        std::string tempResult;
        int v_ume = 0;
        for (int j = 0; j < longNum.size(); ++j)
        {
            int digitLeft = longNum[longNum.size() - 1 - j] - '0';
            int product = digitLeft * digitRight + v_ume;
            v_ume = product / 10;
            tempResult += std::to_string(product % 10);
        }
        if (v_ume > 0)
        {
            tempResult += std::to_string(v_ume);
        }
        std::reverse(tempResult.begin(), tempResult.end());
        for (int k = 0; k < i; ++k)
        {
            tempResult += '0';
        }
        result.longNum = result.add_string_to_string(Longint(tempResult));
    }
    return result.longNum;
}
std::string Longint::longDivision(const Longint& other)
{
    std::string result;
    int index = 0;
    if (other.longNum[0] == '0')
    {
        std::cout << "can't divide by zero\n";
        return "0";
    }
    // extracting the part that is greater than the given divisor
    int dividend = longNum[index] - '0';
    while (dividend < std::stoll(other.longNum))
    {
        dividend = dividend * 10 + (longNum[++index] - '0');
    }
    // iterating until all digits participate in the division
    while (longNum.size() > index)
    {
        result += (dividend / std::stoll(other.longNum)) + '0';
        // adding the next digit to the dividend
        dividend = (dividend % std::stoi(other.longNum)) * 10 + longNum[++index] - '0';
    }
    if (result.length() == 0)
    {
        return "0";
    }
    return result;
}




Longint::Longint(const std::string& str)
{
    if (str[0] == '-')
    {
        longNum = str.substr(1);
        isPos = false;
    }
    else
    {
        longNum = str;
        isPos = true;
    }
}
void Longint::setLong(const std::string& str) {
    longNum = str;
}
std::string Longint::getLong()
{
    return (isPos ? "" : "-") + longNum;
}
int Longint::size() { return longNum.size(); }

void Longint::removeOperationPlus_setMinus( Longint first, Longint other) {
    if (first.longNum.size() > other.longNum.size() ||
        (first.longNum.size() == other.longNum.size() && longNum > other.longNum))
    {
        isPos = true; 
        longNum= sub_string_from_string(other);
    }
    else
    {
        std::string tempstring = longNum;
        first.longNum = other.longNum;
        isPos = true;
        longNum = sub_string_from_string(tempstring);
        isPos = false;
    }
}

void Longint::subTwoPositive(const Longint& other) {
    if (longNum.size() > other.longNum.size() ||
        (longNum.size() == other.longNum.size() && longNum > other.longNum))
    {
        isPos = true;
        longNum = sub_string_from_string(other);
    }
    else
    {
        std::string tempString = longNum;
        longNum = other.longNum;
        isPos = true;
        longNum = sub_string_from_string(tempString);
        isPos = false;
    }
}
void Longint::subTwoNegative(const Longint& other) {
    if (longNum.size() > other.longNum.size() ||
        (longNum.size() == other.longNum.size() && longNum > other.longNum))
    {
        isPos = true;
        longNum = sub_string_from_string(other.longNum);
        isPos = false;
    }
    else
    {
        std::string tempString = longNum;
        longNum = other.longNum;
        isPos = true;
        longNum = sub_string_from_string(tempString);
    }
}
Longint Longint::addLong(const Longint& other)
{
    if (isPos && other.isPos) // x + y
    {
        longNum = add_string_to_string(other);
    }
    else if (!isPos && !other.isPos) //-x + -y = - (x + y)
    {
        isPos = false;
        longNum = add_string_to_string(other);
    }
    else if (isPos && !other.isPos) // x + (-y) = x - y
    {
       
        removeOperationPlus_setMinus(*this, other);
    }
    else // -x + y
    {
        removeOperationPlus_setMinus(other, *this);
    }
    if (longNum == "0") {
        isPos = true;
    }
    return *this;
}
Longint Longint::subLong(const Longint& other)
{
    if (isPos && other.isPos)
        { // x - y
            subTwoPositive(other);
        }
    else if (!isPos && !other.isPos)
        { //(-x) - (-y) = y - x
            subTwoNegative(other);
        }
    else if (isPos && !other.isPos)
        { //(x) - (-y) = x + y
            isPos = true;
            longNum = add_string_to_string(other);
        }
    else if (!isPos && other.isPos)
        { //(-x) - y = -(x + y)
            isPos = false;
            longNum = add_string_to_string(other);
        }
    if (longNum == "0") {
        isPos = true;
    }
    return *this;
}
Longint Longint::multlong(const Longint& other)
{
    if ((isPos && other.isPos) || (!isPos && !other.isPos)) {
        isPos = true;
    }
    else {
        isPos=false;
    }
    
    longNum = multiply_strings(other);
    return *this;
}
Longint Longint::divLong(const Longint& other)
{
    if ((isPos && other.isPos) || (!isPos && !other.isPos)) {
        isPos = true;
    }
    else isPos = false;
    longNum = longDivision(other);
    return *this;
}


Longint Longint::addInt(const int& other)
{   if(other)
    return addLong(Longint(std::to_string(other)));
}
Longint Longint::subInt(const int& other)
{
    return subLong(Longint(std::to_string(other)));
}
Longint Longint::multInt(const int& other)
{
    return multlong(Longint(std::to_string(other)));
}
Longint Longint::divInt(const int& other)
{
    return divLong(Longint(std::to_string(other)));
}



Longint Longint::operator+(const Longint& other) {
    Longint temp = (isPos) ? longNum : "-" + longNum;
    return temp.addLong(other);
}
Longint Longint::operator-(const Longint& other) {
    Longint temp = (isPos) ? longNum : "-" + longNum;
    return temp.subLong(other);
}
Longint Longint::operator*(const Longint& other) {
    Longint temp = (isPos) ? longNum : "-" + longNum;
    return temp.multlong(other);
}
Longint Longint::operator/(const Longint& other) {
    Longint temp = (isPos) ? longNum : "-" + longNum;
    return temp.divLong(other);
}

Longint Longint::operator+=(const Longint& other) {

    return addLong(other);
}
Longint Longint::operator-=(const Longint& other) {
   
    return subLong(other);
}
Longint Longint::operator*=(const Longint& other) {
   
    return multlong(other);
}
Longint Longint::operator/=(const Longint& other) {
    return divLong(other);
}



/*to operation with int */
Longint Longint::operator+(const int& other) {
    Longint temp = (isPos) ? longNum : "-" + longNum;
    return temp.addInt(other);
}
Longint Longint::operator-(const int& other) {
    Longint temp = (isPos) ? longNum : "-" + longNum;
    return temp.subInt(other);
}
Longint Longint::operator*(const int& other) {
    Longint temp = (isPos) ? longNum : "-" + longNum;
    return temp.multInt(other);
}
Longint Longint::operator/(const int& other) {
    Longint temp = (isPos) ? longNum : "-" + longNum;
    return temp.divInt(other);
}
Longint Longint::operator+=(const int& other) {
    return addInt(other);
}
Longint Longint::operator-=(const int& other) {
    return subInt(other);
}
Longint Longint::operator*=(const int& other) {
    return multInt(other);
}
Longint Longint::operator/=(const int& other) {
    return divInt(other);
}



/// /////////////////////////////////////////////////////////

Longint Longint::operator++(int)
{
    Longint temp(*this);
    Longint one("1");
    addLong(one);
    return *this;
}
Longint Longint::operator--(int)
{
    Longint temp(*this);
    Longint one("1");
    subLong(one);
    return *this;
}

bool Longint::operator<=(const Longint& other)
{
    if (isPos && !other.isPos) 
    {
        return false;
    }
    else if (!isPos && other.isPos)
    {
        return true;
    }
    else if (!isPos && !other.isPos)
    {
        return longNum >= other.longNum;
    }
    else
    {
        return longNum <= other.longNum;
    }
}
bool Longint::operator<(const Longint& other)
{
    if (isPos && !other.isPos)
    {
        return false;
    }
    else if (!isPos && other.isPos)
    {
        return true;
    }
    else if (!isPos && !other.isPos)
    {
        return longNum > other.longNum;
    }
    else
    {
        return longNum < other.longNum;
    }
}
bool Longint::operator>=(const Longint& other)
{
    if (isPos && !other.isPos)
    {
        return true;
    }
    else if (!isPos && other.isPos)
    {
        return false;
    }
    else if (!isPos && !other.isPos)
    {
        return longNum <= other.longNum;
    }
    else
    {
        return longNum >= other.longNum;
    }
}
bool Longint::operator>(const Longint& other)
{
    if (isPos && !other.isPos)
    {
        return true;
    }
    else if (!isPos && other.isPos)
    {
        return false;
    }
    else if (!isPos && !other.isPos)
    {
        return longNum < other.longNum;
    }
    else
    {
        return longNum > other.longNum;
    }
}
bool Longint::operator<=(const int& intOther)
{
    Longint other = std::to_string(intOther);
    if (isPos && !other.isPos)
    {
        return false;
    }
    else if (!isPos && other.isPos)
    {
        return true;
    }
    else if (!isPos && !other.isPos)
    {
        return longNum >= other.longNum;
    }
    else
    {
        return longNum <= other.longNum;
    }
}
bool Longint::operator<(const int& intOther)
{
    Longint other = std::to_string(intOther);
    if (isPos && !other.isPos)
    {
        return false;
    }
    else if (!isPos && other.isPos)
    {
        return true;
    }
    else if (!isPos && !other.isPos)
    {
        return longNum > other.longNum;
    }
    else
    {
        return longNum < other.longNum;
    }
}
bool Longint::operator>=(const int& intOther)
{
    Longint other = std::to_string(intOther);
    if (isPos && !other.isPos)
    {
        return true;
    }
    else if (!isPos && other.isPos)
    {
        return false;
    }
    else if (!isPos && !other.isPos)
    {
        return longNum <= other.longNum;
    }
    else
    {
        return longNum >= other.longNum;
    }
}
bool Longint::operator>(const int& intOther)
{
    Longint other = std::to_string(intOther);
    if (isPos && !other.isPos)
    {
        return true;
    }
    else if (!isPos && other.isPos)
    {
        return false;
    }
    else if (!isPos && !other.isPos)
    {
        return longNum < other.longNum;
    }
    else
    {
        return longNum > other.longNum;
    }
}
