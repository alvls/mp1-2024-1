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
    bool operator==(Film& f) const {
        return (this->composer == f.composer &&
            this->date.day == f.date.day &&
            this->date.month == f.date.month &&
            this->date.year == f.date.year &&
            this->director == f.director &&
            this->fees == f.fees &&
            this->screenwriter == f.screenwriter &&
            this->title == f.title);
    }
    bool operator==(const Film& f) const {
        return (this->composer == f.composer &&
            this->date.day == f.date.day &&
            this->date.month == f.date.month &&
            this->date.year == f.date.year &&
            this->director == f.director &&
            this->fees == f.fees &&
            this->screenwriter == f.screenwriter &&
            this->title == f.title);
    }
    bool operator<(Film& f) const {
        if (this->title == f.title) {
            if (this->date.year == f.date.year) {
                if (this->date.month == f.date.month) {
                    return this->date.day < f.date.day;
                }
                else
                {
                    return this->date.month < f.date.month;
                }
            }
            else
            {
                return this->date.year < f.date.year;
            }
        }
        else
        {
            return this->title < f.title;
        }
    }
    bool operator<(const Film& f) const {
        if (this->title == f.title) {
            if (this->date.year == f.date.year) {
                if (this->date.month == f.date.month) {
                    return this->date.day < f.date.day;
                }
                else
                {
                    return this->date.month < f.date.month;
                }
            }
            else
            {
                return this->date.year < f.date.year;
            }
        }
        else
        {
            return this->title < f.title;
        }
    }
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
    FilmLibrary(const vector<Film>& v) {
        sz = v.size();
        for (unsigned int i = 0; i < sz; i++) {
            Film cur = v[i];
            if (exists[cur]) continue;
            exists[cur] = 1;
            films.push_back(cur);
            films_by_fees.insert(cur);
            int k = 0;
            k++;
        }
    }
    void addFilm(const Film& src) {
        if (exists[src]) return;
        exists[src] = 1;
        films.push_back(src);
        films_by_fees.insert(src);
        sz++;
        sort(films.begin(), films.end());
    }
    void changeFilm(const Film& src, const Film& dst) {
        for (unsigned int i = 0; i < sz; i++) {
            if (films[i] == src) {
                films[i] = src;
                sort(films.begin(), films.end());
                return;
            }
        }
        addFilm(dst); // If such film does not exist yet, add it to the film library
    }
    Film findFilm(string title, unsigned int year) {
        bool found = 0;
        for (unsigned int i = 0; i < sz; i++) {
            Film cur = films[i];
            if (cur.title == title && cur.date.year == year) {
                found = 1;
                return cur;
            }
        }
        return Film("", "", "", "", tDate(0, 0, 0), 0);
    }
    vector<Film> filmsByDirector(string director) {
        vector<Film> result;
        for (unsigned int i = 0; i < sz; i++) {
            Film cur = films[i];
            if (cur.director == director) {
                result.push_back(cur);
            }
        }
        return result;
    }
    vector<Film> filmsByYear(unsigned int year) {
        vector<Film> result;
        for (unsigned int i = 0; i < sz; i++) {
            Film cur = films[i];
            if (cur.date.year == year) {
                result.push_back(cur);
            }
        }
        return result;
    }
    vector<Film> topFeesFilms(unsigned int count) {
        vector<Film> result;
        auto it = films_by_fees.begin();
        for (unsigned int i = 0; i < min(count, sz); i++) {
            result.push_back(*it);
            it++;
        }
        return result;
    }
    vector<Film> topFeesFilmsByYear(unsigned int count, unsigned int year) {
        vector<Film> result;
        auto it = films_by_fees.begin();
        unsigned int c = 0;
        for (unsigned int i = 0; i < sz && c < count; i++) {
            Film cur = *it;
            if (cur.date.year == year) {
                result.push_back(*it);
                c++;
            }
            it++;
        }
        return result;
    }
    int size() { return sz; }
    void deleteFilm(const Film& f) {
        if (!exists[f]) return;
        exists[f] = 0;
        sz--;
        unsigned int ind = 0;
        for (unsigned int i = 0; i < sz; i++) {
            if (films[i] == f) {
                ind = i;
                break;
            }
        }
        films.erase(films.begin() + ind);
        films_by_fees.erase(f);
    }
    static bool compareFilmsByFees(const Film& f1, const Film& f2) {
        return film_cmpbyfees(f1, f2);
    }
    void save(string dst) {
        ofstream fout(dst);
        for (int i = 0; i < sz; i++) {
            Film cur = films[i];
            fout << cur.title << " | " << cur.director << " | " << cur.screenwriter << " | " << cur.composer << " | " << cur.date.day << "." << cur.date.month << "." << cur.date.year << " | " << cur.fees;
            fout << endl;
        }
        fout.close();
    }
    void load(string src) {
        ifstream fin(src);
        if (!fin.is_open()) {
            throw "Could not open the file";
        }
        string s;
        Film cur;
        while (getline(fin, s)) {
            istringstream iss(s);
            vector<string> tokens;
            string token;

            while (std::getline(iss, token, '|')) {
                tokens.push_back(token);
            }
            if (tokens.size() != 6) {
                throw "Invalid input file";
            }
            cur.title = tokens[0].substr(0, tokens[0].size() - 1);
            cur.director = tokens[1].substr(1, tokens[1].size() - 2);
            cur.screenwriter = tokens[2].substr(1, tokens[2].size() - 2);
            cur.composer = tokens[3].substr(1, tokens[3].size() - 2);
            tDate t;
            if (tokens[4].size() < 5)
                throw "Invalid date of one of the films";
            istringstream dateiss(tokens[4].substr(1, tokens[4].size() - 2));
            int ind = 0;
            while (getline(dateiss, token, '.')) {
                if (is_numeric(token)) {
                    switch (ind)
                    {
                    case 0:
                        t.day = strtoui(token);
                        break;
                    case 1:
                        t.month = strtoui(token);
                        break;
                    case 2:
                        t.year = strtoui(token);
                        break;
                    }
                }
                else
                {
                    throw "Invalid date of one of the films";
                }
                ind++;
            }
            cur.date = t;
            tokens[5] = tokens[5].substr(1);
            if (is_numeric(tokens[5])) {
                cur.fees = strtoull(tokens[5]);
            }
            else
            {
                throw "Invalid fees of one of the films";
            }
            addFilm(cur);
        }

        fin.close();
    }
};
