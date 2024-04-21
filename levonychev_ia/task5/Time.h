#pragma once
#include <iostream>

struct Time //   0 <= hour <= 23; 0 << minute << 59;
{	
	Time(int hour_, int minute);
	int hour;
	int minute;
	bool operator==(const Time& time) const;
	bool operator!=(const Time& time) const;
	bool operator<(const Time& time) const;
	bool operator>=(const Time& time) const;
	bool operator>(const Time& time) const;
	bool operator<=(const Time& time) const;
	friend std::ostream& operator<<(std::ostream& os, const Time& time);
};