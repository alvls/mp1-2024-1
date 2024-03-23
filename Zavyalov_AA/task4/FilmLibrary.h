#pragma once
#include <string>
#include <set>
#include <vector>

using namespace std;

struct tDate;

struct Film;

bool film_cmpbytitle(Film f1, Film f2);
bool film_cmpbyfees(Film f1, Film f2);

class FilmLibrary // in this realization same films are considered to be one film
{
	vector<Film> films;
	set<Film, decltype(film_cmpbyfees)*> films_by_fees;
	string src = "privet";
	string sadf = src;
	bool s = sadf == src;
public:
	FilmLibrary() {

	}
	void addFilm(Film src) {
		films.push_back(src);
		films_by_fees.insert(src);
	}
	void changeFilm(Film src, Film dst) {
		
	}
};