
#include "D:/LABY/BSUIR/1laba_PPOIS/LongInt.h"
#include <iostream>
#include <string>
#include <algorithm>
const int MAX_INT = 2147483647;
const int MIN_INT = -2147483647;

std::string LongInt::add_string_to_string(const LongInt& other)
{
    std::string sumResult;
    int overflow = 0;
    int maxLength = std::max(int(longNum.size()), int(other.longNum.size()));
    for (int i = 0; i < maxLength; ++i)
    {
        int digitLeft = (i < longNum.size()) ? (longNum[longNum.size() - 1 - i] - '0') : 0;
        int digitRight = (i < other.longNum.size()) ? (other.longNum[other.longNum.size() - 1 - i] - '0') : 0;
        int sum = digitLeft + digitRight + overflow;
        overflow = sum / 10;
        sumResult += std::to_string(sum % 10);
    }
    if (overflow > 0)
    {
        sumResult += std::to_string(overflow);
    }
    std::reverse(sumResult.begin(), sumResult.end());
    return sumResult;
}
std::string LongInt::sub_string_from_string(const LongInt& other)
{
    std::string diffResult;
    int overflow = 0;
    int maxLength = std::max(int(longNum.size()), int(other.longNum.size()));
    for (int i = 0; i < maxLength; ++i)
    {
        int digitLeft = (i < longNum.size()) ? (longNum[longNum.size() - 1 - i] - '0') : 0;
        int digitRight = (i < other.longNum.size()) ? (other.longNum[other.longNum.size() - 1 - i] - '0') : 0;
        int diff = digitLeft - digitRight - overflow;
        overflow = (diff < 0) ? 1 : 0;
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
std::string LongInt::multiply_strings(const LongInt& other)
{
    LongInt result;
    for (int i = 0; i < other.longNum.size(); ++i)
    {
        int digitRight = other.longNum[other.longNum.size() - 1 - i] - '0';
        std::string tempResult;
        int overflow = 0;
        for (int j = 0; j < longNum.size(); ++j)
        {
            int digitLeft = longNum[longNum.size() - 1 - j] - '0';
            int product = digitLeft * digitRight + overflow;
            overflow = product / 10;
            tempResult += std::to_string(product % 10);
        }
        if (overflow > 0)
        {
            tempResult += std::to_string(overflow);
        }
        std::reverse(tempResult.begin(), tempResult.end());
        for (int k = 0; k < i; ++k)
        {
            tempResult += '0';
        }
        result.longNum = result.add_string_to_string(LongInt(tempResult));
    }
    return result.longNum;
}
std::string LongInt::longDivision(const LongInt& other)
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




LongInt::LongInt(const std::string& str)
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
void LongInt::setLong(const std::string& str) {
    longNum = str;
}
std::string LongInt::getLong()
{
    return (isPos ? "" : "-") + longNum;
}
int LongInt::size() { return longNum.size(); }

void LongInt::removeOperationPlus_setMinus( LongInt first, LongInt other) {
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

void LongInt::subTwoPositive(const LongInt& other) {
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
void LongInt::subTwoNegative(const LongInt& other) {
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
LongInt LongInt::addLong(const LongInt& other)
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
LongInt LongInt::subLong(const LongInt& other)
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
LongInt LongInt::multlong(const LongInt& other)
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
LongInt LongInt::divLong(const LongInt& other)
{
    if ((isPos && other.isPos) || (!isPos && !other.isPos)) {
        isPos = true;
    }
    else isPos = false;
    longNum = longDivision(other);
    return *this;
}


LongInt LongInt::addInt(const int& other)
{   if(other)
    return addLong(LongInt(std::to_string(other)));
}
LongInt LongInt::subInt(const int& other)
{
    return subLong(LongInt(std::to_string(other)));
}
LongInt LongInt::multInt(const int& other)
{
    return multlong(LongInt(std::to_string(other)));
}
LongInt LongInt::divInt(const int& other)
{
    return divLong(LongInt(std::to_string(other)));
}



LongInt LongInt::operator+(const LongInt& other) {
    LongInt tempResult = (isPos) ? longNum : "-" + longNum;
    return tempResult.addLong(other);
}
LongInt LongInt::operator-(const LongInt& other) {
    LongInt tempResult = (isPos) ? longNum : "-" + longNum;
    return tempResult.subLong(other);
}
LongInt LongInt::operator*(const LongInt& other) {
    LongInt tempResult = (isPos) ? longNum : "-" + longNum;
    return tempResult.multlong(other);
}
LongInt LongInt::operator/(const LongInt& other) {
    LongInt tempResult = (isPos) ? longNum : "-" + longNum;
    return tempResult.divLong(other);
}

LongInt LongInt::operator+=(const LongInt& other) {

    return addLong(other);
}
LongInt LongInt::operator-=(const LongInt& other) {
   
    return subLong(other);
}
LongInt LongInt::operator*=(const LongInt& other) {
   
    return multlong(other);
}
LongInt LongInt::operator/=(const LongInt& other) {
    return divLong(other);
}



/*to operation with int */
LongInt LongInt::operator+(const int& other) {
    LongInt tempResult = (isPos) ? longNum : "-" + longNum;
    return tempResult.addInt(other);
}
LongInt LongInt::operator-(const int& other) {
    LongInt tempResult = (isPos) ? longNum : "-" + longNum;
    return tempResult.subInt(other);
}
LongInt LongInt::operator*(const int& other) {
    LongInt tempResult = (isPos) ? longNum : "-" + longNum;
    return tempResult.multInt(other);
}
LongInt LongInt::operator/(const int& other) {
    LongInt tempResult = (isPos) ? longNum : "-" + longNum;
    return tempResult.divInt(other);
}
LongInt LongInt::operator+=(const int& other) {
    return addInt(other);
}
LongInt LongInt::operator-=(const int& other) {
    return subInt(other);
}
LongInt LongInt::operator*=(const int& other) {
    return multInt(other);
}
LongInt LongInt::operator/=(const int& other) {
    return divInt(other);
}



/// /////////////////////////////////////////////////////////

LongInt LongInt::operator++(int)
{
    LongInt one("1");
    addLong(one);
    return *this;
}
LongInt LongInt::operator--(int)
{
    LongInt one("1");
    subLong(one);
    return *this;
}

bool LongInt::operator<=(const LongInt& other)
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
bool LongInt::operator<(const LongInt& other)
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
bool LongInt::operator>=(const LongInt& other)
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
bool LongInt::operator>(const LongInt& other)
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
bool LongInt::operator<=(const int& intOther)
{
    LongInt other = std::to_string(intOther);
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
bool LongInt::operator<(const int& intOther)
{
    LongInt other = std::to_string(intOther);
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
bool LongInt::operator>=(const int& intOther)
{
    LongInt other = std::to_string(intOther);
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
bool LongInt::operator>(const int& intOther)
{
    LongInt other = std::to_string(intOther);
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
