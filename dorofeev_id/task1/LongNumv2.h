#pragma once
#include <iostream>

class LongNumv2
{
private:
	bool sign; //true = +; false = -
	unsigned long int p1, p2;

public:
	//constructors
	LongNumv2();
	LongNumv2(int n);
	LongNumv2(int n1, int n2, bool sign);

	//operators
	LongNumv2& operator=(const LongNumv2& other);
	LongNumv2 operator+(const LongNumv2& other) const;
	LongNumv2 operator-(const LongNumv2& other) const;
	LongNumv2 operator*(const LongNumv2& other) const;
	LongNumv2 operator/(const LongNumv2& other) const;
	LongNumv2 operator%(const LongNumv2& other) const;
	friend std::ostream& operator<<(std::ostream& os, const LongNumv2& num);

private:
	LongNumv2 _add(const LongNumv2& other) const;
	LongNumv2 _subtract(const LongNumv2& other) const;
	LongNumv2 _multiply(const LongNumv2& other) const;
	LongNumv2 _divide(const LongNumv2& other) const;

};
