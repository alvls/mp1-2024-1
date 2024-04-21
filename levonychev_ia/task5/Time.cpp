#include "Time.h"
#include <iostream>
#include <ciso646>

Time::Time(int hour_, int minute_): hour(hour_), minute(minute_){}
bool Time::operator==(const Time& time) const
{
	if (hour == time.hour and minute == time.minute)
		return true;
	else
		return false;
}
bool Time::operator!=(const Time& time) const
{
	return !(operator==(time));
}
bool Time::operator<(const Time& time) const
{
	if (hour < time.hour)
		return true;
	else if (hour > time.hour)
		return false;
	else
	{
		if (minute < time.minute)
			return true;
		else
			return false;
	}
}
bool Time::operator>=(const Time& time) const
{
	return !(operator<(time));
}
bool Time::operator>(const Time& time) const
{
	if (hour > time.hour)
		return true;
	else if (hour < time.hour)
		return false;
	else
	{
		if (minute > time.minute)
			return true;
		else
			return false;
	}
}
bool Time::operator<=(const Time& time) const
{
	return !(operator>(time));
}

std::ostream& operator<<(std::ostream& os, const Time& time)
{
	if (time.hour < 10)
		os << "0";
	os << time.hour << ":";
	if (time.minute < 10)
		os << "0";
	os << time.minute;
	return os;
}