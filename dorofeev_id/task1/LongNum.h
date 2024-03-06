#pragma once
#include <iostream>

class LongNum
{
	unsigned int module;
	bool sign;

public:
	//constructors
	LongNum();
	LongNum(int64_t value);
	LongNum(const LongNum& other);

	//operators
	LongNum& operator=(const LongNum& other);
	LongNum& operator+=(const LongNum& other);
	LongNum& operator-=(const LongNum& other);
	LongNum& operator*=(const LongNum& other);
	LongNum& operator/=(const LongNum& other);
	LongNum& operator%=(const LongNum& other);    

	friend std::ostream& operator<<(std::ostream& os, const LongNum& num);
};