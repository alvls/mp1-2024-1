#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct film
{
	string title;
	string director;
	string composer;
	string screenwriter;
	int year;
	int month;
	int day;
	long int box_office;
};

vector<film> fsort(vector<film>& tmp)
{
	sort(tmp.begin(), tmp.end(), [](film& a, film& b)
		{
			if (a.year != b.year)
				return a.year > b.year;
			else
				return a.title < b.title;
		});
	return tmp;
}
class filmoteka
{
	vector <film> films;
public:
	filmoteka() {}
	void add_film(const film& n_film)
	{
		films.push_back(n_film);
		films = fsort(films);
	}
	void change_data(string titl,string dir, int year,const film& edit)
	{
		for (int i = 0; i < films.size(); i++)
		{
			if (films[i].title == titl && films[i].director == dir && films[i].year == year)
				films[i] = edit;
		}
		films = fsort(films);
	}
	film search_film(string titl, int year)
	{
		for (int i = 0; i < films.size(); i++)
		{
			if (films[i].title == titl && films[i].year == year)
				return films[i];
		}
		film ub;
		return ub;
	}
	vector<film> one_director_films(string dir)
	{
		vector<film> tmp;
		for (int i = 0; i < films.size(); i++)
			if (films[i].director == dir)
				tmp.push_back(films[i]);
		return tmp;
	}
	vector<film> one_year_films(int year)
	{
		vector<film> tmp;
		for (int i = 0; i < films.size(); i++)
			if (films[i].year == year)
				tmp.push_back(films[i]);
		return tmp;
	}
	vector<film> top_box_office_films(int top)
	{
		vector<film> tmp;
		if (top > films.size())
			return tmp;
		vector<film> copy = films;
		sort(copy.begin(), copy.end(), [](film& a, film& b)
			{
				return a.box_office > b.box_office;
			});
		for (int i = 0; i < top; i++)
		{
			tmp.push_back(copy[i]);
		}
		return tmp;
	}
	vector<film> top_box_office_this_year_films(int top, int year)
	{
		vector<film> tmp;
		if (top > films.size())
			return tmp;
		vector<film> copy = one_year_films(year);
		sort(copy.begin(), copy.end(), [](film& a, film& b)
			{
				return a.box_office > b.box_office;
			});
		int j = 0;
		for (int i = 0; i < copy.size() && j < top; i++)
		{
			tmp.push_back(copy[i]);
			j++;
		}
		return tmp;
	}
	int GetCountOfFilms()
	{
		return films.size();
	}
	void delete_film(string titl, string dir, int year)
	{
		for (int i = 0; i < films.size(); i++)
		{
			if (films[i].title == titl && films[i].director == dir && films[i].year == year)
			{
				films.erase(films.begin() + i);
				return;
			}	
		}
		films = fsort(films);
	}
	void SaveFile(string name)
	{
		ofstream tmp;
		tmp.open(name);
		if (!tmp.is_open())
			return;
		for (int i = 0; i < films.size(); i++)
		{
			tmp << films[i].title << endl;
			tmp << films[i].director << endl;
			tmp << films[i].composer << endl;
			tmp << films[i].screenwriter << endl;
			tmp << films[i].day <<"."<< films[i].month <<"."<< films[i].year << endl;
			tmp << films[i].box_office<<endl;
		}
		tmp.close();
	}
	void ReadFile(string name)
	{
		ifstream tmpf;
		tmpf.open(name);
		if (!tmpf.is_open())
			return;
		film tmp;
		while (getline(tmpf, tmp.title))
		{
			getline(tmpf, tmp.director);
			getline(tmpf, tmp.composer);
			getline(tmpf, tmp.screenwriter);
			char point;
			tmpf >> tmp.day >> point >> tmp.month >> point >> tmp.year;
			tmpf >> tmp.box_office;
			tmpf.ignore(numeric_limits<streamsize>::max(), '\n');//игнорирование симмвола конца строки для перехода к новому фильму
			//подумал, что наверное можно было бы хранить кассовые сборы в строке, чтобы использовать getline(); -> он получается сам понимает, что ему нужно перевестись на другую строку
			films.push_back(tmp);
		}
		tmpf.close();
		films = fsort(films);
	}
};

int main()//извините за такой невнятный тест класса, просто послезавтра коллоквиум по матанализу((
{
	setlocale(LC_ALL, "rus");
	filmoteka ex1, ex2;
	film A, B, C;
	A.title = "Оппенгеймер";
	A.director = "тест";
	A.composer = "Людвиг Горанссон";
	A.screenwriter = "Мартин Шервин";
	A.day = 19;
	A.month = 7;
	A.year = 2023;
	A.box_office = 329862540;
	ex1.add_film(A);
	B.title = "Зеленая миля";
	B.director = "Фрэнк Дарабонт";
	B.composer = "Томас Ньюман";
	B.screenwriter = "Стивен Кинг";
	B.day = 6;
	B.month = 12;
	B.year = 1999;
	B.box_office = 286801374;
	ex1.add_film(B);
	C.title = "Бойцовский клуб";
	C.director = "тест";
	C.composer = "Даст Бразерс";
	C.screenwriter = "Чак Паланик";
	C.day = 10;
	C.month = 9;
	C.year = 1999;
	C.box_office = 100853753;
	ex1.add_film(C);
	ex1.SaveFile("Films.txt");
	ex2.ReadFile("Films.txt");
	ex2.SaveFile("Films2.txt");
	film tmp;
	tmp.title = "Смешарики";
	tmp.composer = "кто то";
	tmp.director = "кто то там";
	tmp.screenwriter = "кто то там еще";
	tmp.day = 1;
	tmp.month = 1;
	tmp.year = 1;
	tmp.box_office = 10000;
	ex2.change_data("Бойцовский клуб", "тест", 1999, tmp);
	ex2.SaveFile("test smeshariki change data.txt");
	ex2.delete_film("Смешарики", "кто то там", 1);
	ex2.SaveFile("test smeshariki delete film.txt");
	vector<film> vec = ex1.one_director_films("тест");
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i].title << endl;
	cout << endl;
	vec = ex1.top_box_office_this_year_films(2, 1999);
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i].title << endl;
	cout << endl;
	vec = ex1.top_box_office_films(2);
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i].title << endl;
	system("pause");
}