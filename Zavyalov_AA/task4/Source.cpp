#include "FilmLibrary.h"
#include <iostream>

int main() {
	setlocale(LC_ALL, "ru");
	/*string title;
	string director;
	string screenwriter;
	string composer;
	tDate date;
	unsigned long long fees;*/
	tDate g(1, 1, 1);
	Film f("джек воробей", "дирик", "скринрайтер", "композер", g, 123);
	std::cout << f.composer;
	FilmLibrary fl;
	fl.addFilm(f);

	system("pause");
	return 0;
}