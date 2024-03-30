#include "FilmLibrary.h"

bool film_cmpbytitle(const Film& f1, const Film& f2) {
	if (f1.title == f2.title) {
		if (f1.date.year == f2.date.year) {
			if (f1.date.month == f2.date.month) {
				return f1.date.day < f2.date.day;
			}
			else
			{
				return f1.date.month < f2.date.month;
			}
		}
		else
		{
			return f1.date.year < f2.date.year;
		}
	}
	else
	{
		return f1.title < f2.title;
	}
}

bool film_cmpbyfees(const Film& f1, const Film& f2) {
	return (f1.fees > f2.fees);
}

bool is_numeric(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] < '0' || s[i] > '9') return 0;
	}
	return 1;
}

unsigned int strtoui(string s) {
	unsigned int res = 0, mult = 1;
	for (int i = s.length() - 1; i >= 0; i--) {
		res += (s[i] - '0') * mult;
		mult *= 10;
	}
	return res;
}

unsigned long long strtoull(string s) {
	unsigned long long res = 0, mult = 1;
	for (int i = s.length() - 1; i >= 0; i--) {
		res += (s[i] - '0') * mult;
		mult *= 10;
	}
	return res;
}