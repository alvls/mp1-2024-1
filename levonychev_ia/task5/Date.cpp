#include "Date.h"
#include <iostream>
#include <ciso646>

Date::Date(int day_, int month_, int year_): day(day_), month(month_), year(year_) {}

bool Date::operator==(const Date& date) const
{
	if (day == date.day and month == date.month and year == date.year)
	{
		return true;
	}
	else
		return false;
}

bool Date::operator!=(const Date& date) const
{
	return !(operator==(date));
}

bool Date::operator<(const Date& date) const
{
	if (year < date.year)
		return true;
	else if (year > date.year)
		return false;
	else
	{
		if (month < date.month)
			return true;
		else if (month > date.month)
			return false;
		else
		{
			if (day < date.day)
				return true;
			else
				return false;
		}
	}
}

bool Date::operator>=(const Date& date) const
{
	return !(operator<(date));
}

bool Date::operator>(const Date& date) const
{
	if (year > date.year)
		return true;
	else if (year < date.year)
		return false;
	else
	{
		if (month > date.month)
			return true;
		else if (month < date.month)
			return false;
		else
		{
			if (day > date.day)
				return true;
			else
				return false;
		}
	}
}
bool Date::operator<=(const Date& date) const
{
	return !(operator>(date));
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	if (date.day < 10)
		os << "0";
	os << date.day << ".";
	if (date.month < 10)
		os << "0";
	os << date.month << ".";
	os << date.year;
	return os;
}