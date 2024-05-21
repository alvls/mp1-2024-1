#include "Movie.h"

bool Movie::operator <(const Movie& b) const {
	if (title == b.title) {
		if (date.year == b.date.year && date.month == b.date.month) return date.day < b.date.day;
		else if (date.year == b.date.year) return date.month < b.date.month;
		else return date.year < b.date.year;
	}
	return (title < b.title);
}

bool Movie::operator ==(const Movie& b) const {
	return (title == b.title &&
		director == b.director &&
		screenwriter == b.screenwriter &&
		composer == b.composer &&
		date.year == b.date.year &&
		date.month == b.date.month &&
		date.day == b.date.day &&
		profit == b.profit);
}

void MovieLibrary::addMovie(const Movie& movie) {
	movies.insert(movie);
}

void MovieLibrary::addMovie(const vector<Movie>& newMovies) {
	for (Movie x : newMovies) movies.insert(x);
}

void MovieLibrary::modifyMovie(const Movie& lm, const Movie& nm) {
	auto it = movies.find(lm);
	if (it != movies.end()) {
		movies.erase(it);
		Movie tmp = *it;
		tmp.director = nm.director;
		tmp.screenwriter = nm.screenwriter;
		tmp.composer = nm.composer;
		tmp.date.day = nm.date.day;
		tmp.date.month = nm.date.month;
		tmp.date.year = nm.date.year;
		tmp.profit = nm.profit;
		addMovie(tmp);
	}
}

Movie MovieLibrary::findMovieByTitleAndYear(const string& title, int year) {
	for (Movie movie : movies) {
		if (movie.title == title && movie.date.year == year) {
			return movie;
		}
	}
	return Movie("", "", "", "", { 0,0,0 }, 0);
}

vector<Movie> MovieLibrary::findMovieByDirector(const string& director) {
	vector<Movie> foundMovies;
	for (Movie movie : movies) {
		if (movie.director == director) {
			foundMovies.push_back(movie);
		}
	}
	return foundMovies;
}

vector<Movie> MovieLibrary::findMovieByYear(int year) {
	vector<Movie> foundMovies;
	for (Movie movie : movies) {
		if (movie.date.year == year) {
			foundMovies.push_back(movie);
		}
	}
	return foundMovies;
}

vector<Movie> MovieLibrary::findTopNMoviesByProfit(int n) {
	vector<Movie> tmp;
	for (Movie x : movies) tmp.push_back(x);
	vector<Movie> foundMovies;
	sort(tmp.begin(), tmp.end(), [](const Movie& a, const Movie& b) { return a.profit > b.profit; });
	if (tmp.size() <= n) return tmp;
	else {
		for (int i = 0; i < n; i++) foundMovies.push_back(tmp[i]);
	}
	return foundMovies;
}

vector<Movie> MovieLibrary::findTopNMoviesByProfitInYear(int n, int year) {
	vector<Movie> foundMovies;
	vector<Movie> tmp;
	for (Movie movie : movies) {
		if (movie.date.year == year) {
			foundMovies.push_back(movie);
		}
	}
	sort(foundMovies.begin(), foundMovies.end(), [](const Movie& a, const Movie& b) {return a.profit > b.profit; });
	if (n >= foundMovies.size()) return foundMovies;
	else {
		for (int i = 0; i < n; i++) tmp.push_back(foundMovies[i]);
	}
	return tmp;
}

int MovieLibrary::GetSize() {
	return movies.size();
}

void MovieLibrary::DeleteMovie(const Movie& dm) {
	auto it = movies.find(dm);
	if (it != movies.end()) {
		movies.erase(it);
	}
}

void MovieLibrary::SaveToFile(const string& filename) {
	ofstream fout(filename);
	for (Movie m : movies) {
		fout << "Название: " << m.title << '\n';
		fout << "Режиссёр: " << m.director << '\n';
		fout << "Сценарист: " << m.screenwriter << '\n';
		fout << "Композитор: " << m.composer << '\n';
		fout << "Дата выхода в прокат: " << m.date.day << '.' << m.date.month << '.' << m.date.year << '\n';
		fout << "Сборы: " << m.profit << '\n';
		fout << "------------------------" << '\n';
	}
	fout.close();
}

void MovieLibrary::LoadFromFile(const std::string& filename) {
	ifstream file(filename);
	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		string title, director, screenwriter, composer;
		int day, month, year, profit;
		getline(iss, title, ',');
		getline(iss, director, ',');
		getline(iss, screenwriter, ',');
		getline(iss, composer, ',');
		iss >> day >> month >> year >> profit;
		addMovie(Movie(title, director, screenwriter, composer, { day, month, year }, profit));
	}
	file.close();
}

void MovieLibrary::show() {
	for (Movie x : movies) {
		cout << "Название: " << x.title << '\n';
		cout << "Режиссёр: " << x.director << '\n';
		cout << "Сценарист: " << x.screenwriter << '\n';
		cout << "Композитор: " << x.composer << '\n';
		cout << "Дата выхода в прокат: " << x.date.day << '.' << x.date.month << '.' << x.date.year << '\n';
		cout << "Сборы: " << x.profit << '\n';
		cout << "------------------------" << '\n';
	}
}

