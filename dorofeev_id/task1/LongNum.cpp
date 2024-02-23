#include "LongNum.h"

//constructors
LongNum::LongNum() : module(0), sign(false) {}
LongNum::LongNum(int64_t value)
{
    if (value < 0)
    {
        sign = true;
        value = -value;
    }
    else
    {
        sign = false;
    }
    module = value;
}
LongNum::LongNum(const LongNum& other)
{
    module = other.module;
    sign = other.sign;
}

//operators
LongNum& LongNum::operator=(const LongNum& other) 
{
  if (this == &other) 
  {
    return *this;
  }

  module = other.module;
  sign = other.sign;
  return *this;
}

LongNum& LongNum::operator+=(const LongNum& other) 
{
    if (sign == other.sign) 
    {
        // ѕроверка переполнени€ при сложении
        if (module + other.module > UINT_MAX) 
        {
            module = UINT_MAX;
            sign = true;
        }
        else 
        {
            module += other.module;
        }
    }
    else if (module > other.module) 
    {
        module -= other.module;
    }
    else 
    {
        module = other.module - module;
        sign = other.sign;
    }
    return *this;
}


LongNum& LongNum::operator-=(const LongNum& other) 
{
    if (sign == other.sign) 
    {
        if (module > other.module) 
        {
            module -= other.module;
        }
        else 
        {
            module = other.module - module;
            sign = !sign;
        }
    }
    else {
        // ѕроверка переполнени€ при вычитании
        if (module + other.module > UINT_MAX) 
        {
            module = UINT_MAX;
            sign = false;
        }
        else 
        {
            module += other.module;
        }
    }
    return *this;
}


LongNum& LongNum::operator*=(const LongNum& other) 
{
    // ѕроверка переполнени€ при умножении
    if (module > UINT_MAX / other.module) 
    {
        module = UINT_MAX;
        sign = true;
    }
    else 
    {
        module *= other.module;
        sign ^= other.sign;
    }
    return *this;
}


LongNum& LongNum::operator/=(const LongNum& other)
{
    if (other.module == 0)
    {
        throw std::runtime_error("Division by zero");
    }

    bool negative = sign ^ other.sign;
    sign = false;

    if (module < other.module)
    {
        module = 0;
    }
    else
    {
        uint64_t dividend = (uint64_t)module;
        uint64_t divisor = (uint64_t)other.module;
        uint64_t quotient = 0;

        while (dividend >= divisor)
        {
            dividend -= divisor;
            quotient++;
        }

        module = quotient;
    }

    if (negative)
    {
        sign = true;
    }

    return *this;
}



LongNum& LongNum::operator%=(const LongNum& other)
{
    if (other.module == 0)
    {
        throw std::runtime_error("Division by zero");
    }

    bool negative = sign ^ other.sign;
    sign = false;

    if (module < other.module)
    {
        // ≈сли модуль меньше делител€, остаток равен модулю
        return *this;
    }
    else
    {
        uint64_t dividend = (uint64_t)module;
        uint64_t divisor = (uint64_t)other.module;

        // ѕроходим через деление дл€ получени€ остатка
        while (dividend >= divisor)
        {
            dividend -= divisor;
        }

        module = dividend;
    }

    if (negative)
    {
        sign = true;
    }

    return *this;
}


