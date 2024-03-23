#pragma once
#include <string>
#include <set>
#include <vector>
#include <locale>

using namespace std;

struct tDate {
	unsigned int day;
	unsigned int month;
	unsigned int year;
	tDate(unsigned int day_, unsigned int month_, unsigned int year_) {
		day = day_;
		month = month_;
		year = year_;
	}
	tDate() {};
};

struct Film
{
	string title;
	string director;
	string screenwriter;
	string composer;
	tDate date;
	unsigned long long fees=0;
	Film(string title_, string director_, string screenwriter_, string composer_, tDate date_, unsigned long long fees_) {
		title = title_;
		director = director_;
		screenwriter = screenwriter_;
		composer = composer_;
		date = date_;
		fees = fees_;
	}
	Film() {};
};

bool film_cmpbytitle(Film f1, Film f2);
bool film_cmpbyfees(Film f1, Film f2);

class FilmLibrary // in this realization same films are considered to be one film
{
	vector<Film> films;
	set<Film, decltype(film_cmpbyfees)*> films_by_fees;
	unsigned int sz = 0;
public:
	FilmLibrary() {

	}
	void addFilm(Film src) {
		films.push_back(src);
		films_by_fees.insert(src);
	}
	void changeFilm(Film src, Film dst) { // переписать на бинарный поиск
		for (int i = 0; i < sz; i++) {
			if (films[i] == src) { // Написать перегрузку operator==

			}
		}
	}
};