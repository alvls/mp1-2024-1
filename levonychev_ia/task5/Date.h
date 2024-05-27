#pragma once
#include <iostream>

struct Date //    1 << day << 31;  1 << month << 12;
{	
	Date(int day_, int month_, int year);
	int day;
	int month;
	int year;
	bool operator==(const Date& date) const;
	bool operator!=(const Date& date) const;
	bool operator<(const Date& date) const;
	bool operator>=(const Date& date) const;
	bool operator>(const Date& date) const;
	bool operator<=(const Date& date) const;
	friend std::ostream& operator<<(std::ostream& os, const Date& date);
};