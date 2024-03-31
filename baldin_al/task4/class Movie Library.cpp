#include "Movie.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	MovieLibrary Netflix;
	Netflix.LoadFromFile("input.txt");
	Movie a("The Matrix", "The Wachowskis", "The Wachowskis", "Don Davis", { 31, 3, 1999 }, 872775774);
	Netflix.addMovie(a);
	Netflix.addMovie(a);
	Netflix.show();
	cout << '\n';
	Movie f = Netflix.findMovieByTitleAndYear("Titanic", 1997);
	cout << f.title << ' ' << f.date.year << ' ' << f.profit << '\n';
	cout << '\n';
	for (Movie x : Netflix.findMovieByDirector(" James Cameron")) cout << x.title << ' ';
	cout << '\n';
	for (Movie x : Netflix.findMovieByYear(2000)) cout << x.title << ' ';
	cout << '\n';
	for (Movie x : Netflix.findTopNMoviesByProfit(3)) cout << x.title << ' ';
	cout << '\n';
	for (Movie x : Netflix.findTopNMoviesByProfitInYear(3, 2014)) cout << x.title << ' ';
	cout << '\n';
	cout << Netflix.GetSize() << '\n';
	Netflix.DeleteMovie(a);
	Netflix.SaveToFile("output.txt");

	system("pause");
}