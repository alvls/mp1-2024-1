#include "LongNumv2.h"

// Constructors
LongNumv2::LongNumv2() : sign(true), p1(0), p2(0) {}

LongNumv2::LongNumv2(int n) 
{
    sign = n >= 0;
    unsigned long long abs_n = std::abs(static_cast<long long>(n));
    unsigned int* parts = reinterpret_cast<unsigned int*>(&abs_n);
    p1 = parts[1];
    p2 = parts[0];
}

LongNumv2::LongNumv2(unsigned long int n1, unsigned long int n2, bool s)
{
    sign = s;
    p1 = n1;
    p2 = n2;
}


// Operators
LongNumv2& LongNumv2::operator=(const LongNumv2& other) 
{
    if (this != &other) 
    {
        sign = other.sign;
        p1 = other.p1;
        p2 = other.p2;
    }
    return *this;
}

LongNumv2 LongNumv2::operator+(const LongNumv2& other) const 
{
    if (sign == other.sign) 
    {
        return _add(other);
    }
    else 
    {
        return _subtract(other);
    }
}

LongNumv2 LongNumv2::operator-(const LongNumv2& other) const {

    if (sign == other.sign) 
    {
        return _subtract(other);
    }
    else 
    {
        return _add(other);
    }
}

LongNumv2 LongNumv2::operator*(const LongNumv2& other) const 
{
    return _multiply(other);
}

LongNumv2 LongNumv2::operator/(const LongNumv2& other) const 
{
    return _divide(other);
}

LongNumv2 LongNumv2::operator%(const LongNumv2& other) const 
{
    LongNumv2 quotient = _divide(other);
    LongNumv2 remainder = *this - (other * quotient);
    return remainder;
}

bool LongNumv2::operator==(const LongNumv2& other) const 
{
    return sign == other.sign && p1 == other.p1 && p2 == other.p2;
}

std::ostream& operator<<(std::ostream& os, const LongNumv2& num) 
{
    if (!num.sign)
        os << "-";

    if (num.p1 != 0)
        std::cout << num.p1;

    std::cout << num.p2;

    return os;
}


LongNumv2 LongNumv2::_add(const LongNumv2& other) const 
{
    unsigned long long sum = (static_cast<unsigned long long>(p1) << 32) | p2;
    sum += (static_cast<unsigned long long>(other.p1) << 32) | other.p2;

    unsigned int new_p2 = sum & 0xFFFFFFFF;
    unsigned int new_p1 = sum >> 32;
    return LongNumv2(new_p1, new_p2, sign);
}

LongNumv2 LongNumv2::_subtract(const LongNumv2& other) const 
{
    unsigned long long thisValue = _toUnsignedLongLong();
    unsigned long long otherValue = other._toUnsignedLongLong();
    bool result_sign = sign;

    if (thisValue < otherValue) 
    {
        std::swap(thisValue, otherValue);
        result_sign = !result_sign;
    }

    unsigned long long resultValue = thisValue - otherValue;

    return LongNumv2(resultValue >> 32, resultValue & 0xFFFFFFFF, result_sign);
}

LongNumv2 LongNumv2::_multiply(const LongNumv2& other) const 
{
    unsigned long long num1 = (static_cast<unsigned long long>(p1) << 32) | p2;
    unsigned long long num2 = (static_cast<unsigned long long>(other.p1) << 32) | other.p2;

    bool result_sign = (sign == other.sign);

    unsigned long long result = num1 * num2;

    unsigned int result_p1 = static_cast<unsigned int>(result >> 32);
    unsigned int result_p2 = static_cast<unsigned int>(result);

    return LongNumv2(result_p1, result_p2, result_sign);
}

LongNumv2 LongNumv2::_divide(const LongNumv2& other) const 
{
    if (other == LongNumv2(0)) 
    {
        std::cerr << "Division by zero" << std::endl;
        exit(1);
    }

    unsigned long long num1 = (static_cast<unsigned long long>(p1) << 32) | p2;
    unsigned long long num2 = (static_cast<unsigned long long>(other.p1) << 32) | other.p2;

    bool result_sign = (sign == other.sign);

    unsigned long long quotient = num1 / num2;

    unsigned int quotient_p1 = static_cast<unsigned int>(quotient >> 32);
    unsigned int quotient_p2 = static_cast<unsigned int>(quotient & 0xFFFFFFFF);

    return LongNumv2(quotient_p1, quotient_p2, result_sign);
}

unsigned long long LongNumv2::_toUnsignedLongLong() const
{
    return (static_cast<unsigned long long>(p1) << 32) | p2;
}

