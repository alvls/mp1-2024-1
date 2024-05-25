#pragma once
#include <string>
#include <set>
#include <vector>
#include <locale>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

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
    tDate() = default;
};

struct Film
{
    string title;
    string director;
    string screenwriter;
    string composer;
    tDate date;
    unsigned long long fees = 0;
    Film(string title_, string director_, string screenwriter_, string composer_, tDate date_, unsigned long long fees_) {
        title = title_;
        director = director_;
        screenwriter = screenwriter_;
        composer = composer_;
        date = date_;
        fees = fees_;
    }
    Film() = default;
    bool operator==(Film& f) const;
    bool operator==(const Film& f) const;
    bool operator<(Film& f) const;
    bool operator<(const Film& f) const;
};

bool film_cmpbytitle(const Film& f1, const Film& f2);
bool film_cmpbyfees(const Film& f1, const Film& f2);
bool is_numeric(string s);
unsigned int strtoui(string s);
unsigned long long strtoull(string s);

class FilmLibrary
{
    vector<Film> films;
    map<Film, bool> exists;
    set<Film, bool (*)(const Film&, const Film&)> films_by_fees{ compareFilmsByFees };
    unsigned int sz = 0;
public:
    FilmLibrary() {}
    FilmLibrary(const vector<Film>& v);
    void addFilm(const Film& src);
    void changeFilm(const Film& src, const Film& dst);
    Film findFilm(string title, unsigned int year);
    vector<Film> filmsByDirector(string director);
    vector<Film> filmsByYear(unsigned int year);
    vector<Film> topFeesFilms(unsigned int count);
    vector<Film> topFeesFilmsByYear(unsigned int count, unsigned int year);
    int size();
    void deleteFilm(const Film& f);
    static bool compareFilmsByFees(const Film& f1, const Film& f2) {return film_cmpbyfees(f1, f2);}
    void save(string dst);
    void load(string src);
};
