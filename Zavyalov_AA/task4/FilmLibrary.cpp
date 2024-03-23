#include "FilmLibrary.h"

struct tDate {
	unsigned int day;
	unsigned int month;
	unsigned int year;
};

struct Film
{
	string title;
	string director;
	string screenwriter;
	string composer;
	tDate date;
	unsigned long long fees;
};

bool film_cmpbytitle(Film f1, Film f2) {
	if (f1.title == f2.title) {
		if (f1.date.year == f2.date.year) {
			if (f1.date.month == f2.date.month) {
				return f1.date.day <= f2.date.day;
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

bool film_cmpbyfees(Film f1, Film f2) {
	return (f1.fees > f2.fees);
}
