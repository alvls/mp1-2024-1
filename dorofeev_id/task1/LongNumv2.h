#pragma once
#include <iostream>

class LongNumv2 {
private:
    bool sign; // true = +; false = -
    unsigned int p1, p2;

public:
    // Constructors
    LongNumv2();
    LongNumv2(int n);
    LongNumv2(int n1, int n2, bool sign);

    // Operators
    LongNumv2& operator=(const LongNumv2& other);
    LongNumv2 operator+(const LongNumv2& other) const;
    LongNumv2 operator-(const LongNumv2& other) const;
    LongNumv2 operator*(const LongNumv2& other) const;
    LongNumv2 operator/(const LongNumv2& other) const;
    LongNumv2 operator%(const LongNumv2& other) const;
    bool operator==(const LongNumv2& other) const;
    friend std::ostream& operator<<(std::ostream& os, const LongNumv2& num);

private:
    LongNumv2 _add(const LongNumv2& other) const;
    LongNumv2 _subtract(const LongNumv2& other) const;
    LongNumv2 _multiply(const LongNumv2& other) const;
    LongNumv2 _divide(const LongNumv2& other) const;
    unsigned long long _toUnsignedLongLong() const;
};
