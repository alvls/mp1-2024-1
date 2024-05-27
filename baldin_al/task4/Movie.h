#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <locale>
#include <fstream>
#include <sstream>

using namespace std;

struct Release_date {
	int day;
	int month;
	int year;
};

struct Movie {
	string title;
	string director;
	string screenwriter;
	string composer;
	Release_date date;
	long long profit;
	Movie(const string& title_, const string& director_, const string& screenwriter_,
		const string& composer_, const Release_date& date_, long long profit_)
	{
		title = title_; director = director_; screenwriter = screenwriter_;
		composer = composer_; date = date_; profit = profit_;
	}
	bool operator <(const Movie& b) const;
	bool operator ==(const Movie& b) const;
};

class MovieLibrary {
	set <Movie> movies;

public:
	MovieLibrary() {};

	void addMovie(const Movie& movie);

	void addMovie(const vector<Movie>& newMovies);

	void modifyMovie(const Movie& lm, const Movie& nm);

	Movie findMovieByTitleAndYear(const string& title, int year);

	vector<Movie> findMovieByDirector(const string& director);

	vector<Movie> findMovieByYear(int year);

	vector<Movie> findTopNMoviesByProfit(int n);

	vector<Movie> findTopNMoviesByProfitInYear(int n, int year);

	int GetSize();

	void DeleteMovie(const Movie& dm);

	void SaveToFile(const string& filename);

	void LoadFromFile(const string& filename);

	void show();
};