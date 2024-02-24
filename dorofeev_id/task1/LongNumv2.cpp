#include "LongNumv2.h"


//constructors
LongNumv2::LongNumv2() {}
LongNumv2::LongNumv2(int n)
{
    sign = n >= 0;

    unsigned long long abs_n = static_cast<unsigned long long>(std::abs(n));

    p1 = abs_n >> 32;
    p2 = abs_n & 0xFFFFFFFF;
}



LongNumv2::LongNumv2(int n1, int n2, bool sign)
{
    p1 = n1;
    p2 = n2;
}
//operators
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
LongNumv2 LongNumv2::operator-(const LongNumv2& other) const
{
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

std::ostream& operator<<(std::ostream& os, const LongNumv2& num)
{
    if (!num.sign)
        os << "-";

    if (num.p1 != 0)
        os << num.p1;

    os << num.p2;

    return os;
}



LongNumv2 LongNumv2::_add(const LongNumv2& other) const
{
    int s1 = p1 + other.p1;
    int s2 = p2 + other.p2;

    if (s2 >= 0x100000000)
    {
        s2 -= 0x100000000;
        s1++;
    }

    return LongNumv2(s1, s2, sign);
}

LongNumv2 LongNumv2::_subtract(const LongNumv2& other) const
{
    if (sign == other.sign)
    {
        bool thisIsBigger = false;
        if (p1 > other.p1) 
        {
            thisIsBigger = true;
        }
        else if (p1 == other.p1)
        {
            thisIsBigger = (p2 >= other.p2);
        }

        if (!thisIsBigger) 
        {
            LongNumv2 result = other._subtract(*this);
            result.sign = !result.sign;
            return result;
        }

        unsigned long long result_p1 = p1;
        unsigned long long result_p2 = p2;

        if (p2 < other.p2) 
        {
            result_p1--;
            result_p2 += 0x100000000;
        }

        result_p1 -= other.p1;
        result_p2 -= other.p2;

        return LongNumv2(result_p1, result_p2, sign);
    }
    else
    {
        LongNumv2 temp = other;
        temp.sign = !temp.sign;

        return _add(temp);
    }
}

LongNumv2 LongNumv2::_multiply(const LongNumv2& other) const
{
    unsigned long long num1 = (static_cast<unsigned long long>(p1) << 32) | p2;
    unsigned long long num2 = (static_cast<unsigned long long>(other.p1) << 32) | other.p2;

    bool result_sign = (sign == other.sign);

    unsigned long long result = num1 * num2;

    unsigned long int result_p1 = static_cast<unsigned long int>(result >> 32);
    unsigned long int result_p2 = static_cast<unsigned long int>(result);

    return LongNumv2(result_p1, result_p2, result_sign);
}



LongNumv2 LongNumv2::_divide(const LongNumv2& other) const
{
    unsigned long long num1 = (static_cast<unsigned long long>(p1) << 32) | p2;
    unsigned long long num2 = (static_cast<unsigned long long>(other.p1) << 32) | other.p2;

    bool result_sign = (sign == other.sign);

    unsigned long long quotient = num1 / num2;

    unsigned long int quotient_p1 = quotient >> 32;
    unsigned long int quotient_p2 = quotient & 0xFFFFFFFF;

    return LongNumv2(quotient_p1, quotient_p2, result_sign);
}
