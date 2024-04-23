#include "Cinema.h"
#include <iostream>
#include <ciso646>
Hall::Hall(unsigned hall_number_, unsigned row_count_, unsigned seat_count_) : hall_number(hall_number_), row_count(row_count_), seat_count(seat_count_) {}
MovieSession::MovieSession(Date date_, Time time_, std::string name_, Hall hall_, double base_cost_): date(date_), time(time_), name(name_), hall(hall_), base_cost(base_cost_) {}
bool MovieSession::operator==(const MovieSession& a)
{
	if (date == a.date and time == a.time and name == a.name and base_cost == a.base_cost)
		return true;
	else
		return false;
}

void Cinema::add_hall( Hall& a)
{
	for (Hall& b : halls)
	{
		if (b.hall_number == a.hall_number)
		{
			throw std::invalid_argument("The hall already exists!");
		}
	}
	halls.push_back(a);
}
void Cinema::add_movie_session(Date date, Time time, std::string name, Hall hall, double base_cost)
{	
	movie_sessions.push_back({ date, time, name, hall, base_cost});
}
void Cinema::info()
{	
	using namespace std;
	int i = 1;
	for (MovieSession& a : movie_sessions)
	{
		cout << i << "." << endl;
		cout << "Name: " << a.name << endl;
		cout << "Hall " << a.hall.hall_number << endl;
		cout << "Date: " << a.date << endl;
		cout << "Time: " << a.time << endl;
		cout << "Base price: " << a.base_cost << "p." << endl << endl;
		++i;
	}
}