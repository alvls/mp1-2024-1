#include <string>
#include <iostream>
#include <ciso646>
#include <ctime>
#include "TicketOffice.h"
TicketOffice::TicketOffice(Cinema& cinema_) : cinema(cinema_) {}
double TicketOffice::buy_tickets(Date date, Time time, std::string name, unsigned hall_number, unsigned seat_type, unsigned count_of_tickets)
{	

	std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);

	int current_hour = now->tm_hour;
	int current_min = now->tm_min;
	int current_day = now->tm_mday;
	int current_month = (now->tm_mon + 1);
	int current_year = (now->tm_year + 1900);
	Time current_time(current_hour, current_min);
	Date current_date(current_day, current_month, current_year);

	if (current_date > date or (current_date == date and current_time > time))
		throw std::invalid_argument("Error!");
	Hall* hall_ptr = nullptr;
	for (Hall& a : cinema.halls)
	{
		if (a.hall_number == hall_number)
		{
			hall_ptr = &a;
		}
	}
	if (hall_ptr == nullptr)
	{
		throw std::invalid_argument("Error!");
	}

	MovieSession* movie_session_ptr = nullptr;
	for (MovieSession& a : cinema.movie_sessions)
	{
		if (a.name == name and a.hall.hall_number == hall_number and a.date == date and a.time == time)
		{
			movie_session_ptr = &a;
		}
	}
	if (movie_session_ptr == nullptr)
	{
		throw std::invalid_argument("Error!");
	}
	if (count_of_tickets > movie_session_ptr->free_seats)
		throw std::invalid_argument("Error!");
	srand(std::time(NULL));
	for (int i = 0; i < count_of_tickets; i++)
	{	
		int flag = 1;
		int seat_number;
		do
		{
			seat_number = 1 + rand() % (hall_ptr->row_count * hall_ptr->seat_count);
			for (int k : movie_session_ptr->occupied_seats)
			{
				if (k == seat_number)
				{
					flag = 0;
					break;
				}
				flag = 1;
			}
		} while (flag == 0);
		movie_session_ptr->occupied_seats.push_back(seat_number);
	}
	double price;
	price = movie_session_ptr->base_cost * count_of_tickets;
	if (seat_type == 1)
		price *= 2;
	if (time.hour < 12)
		price *= 0.75;
	if (time.hour > 18)
		price *= 1.5;
	movie_session_ptr->free_seats -= count_of_tickets;
	std::cout << "----TICKET----" << std::endl;
	std::cout << "Movie: \"" << name << "\"" << std::endl;
	std::cout << "Date: " << date << std::endl;
	std::cout << "Time: " << time << std::endl;
	std::cout << "Hall " << hall_ptr->hall_number << std::endl;
	std::cout << "Count of tickets: " << count_of_tickets << std::endl;
	std::cout << "Type: ";
	if (seat_type == 0)
		std::cout << "base" << std::endl;
	if (seat_type == 1)
		std::cout << "VIP" << std::endl;
	int size = movie_session_ptr->occupied_seats.size();
	for (int i = 1; i <= count_of_tickets; i++)
	{	
		int row_number;
		int seat_number;
		if (movie_session_ptr->occupied_seats[size - i] % hall_ptr->seat_count == 0)
		{
			row_number = movie_session_ptr->occupied_seats[size - i] / (hall_ptr->seat_count);
			seat_number = 15;
		}
		else
		{
			row_number = movie_session_ptr->occupied_seats[size - i] / (hall_ptr->seat_count) + 1;
			seat_number = movie_session_ptr->occupied_seats[size - i] % hall_ptr->seat_count;
		}
		
		std::cout << i << ") " << "Row " << row_number << ", Seat " << seat_number << std::endl;
	}
	std::cout << "----" << std::endl;
	std::cout << "TOTAL PRICE: " << price << std::endl;
	std::cout << "----" << std::endl << std::endl;
	return price;

}
void TicketOffice::cancel_order(MovieSession& a, unsigned count)
{	
	int flag = 0;
	for (MovieSession& b : cinema.movie_sessions)
	{
		if (a == b)
		{
			for (int i = 1; i <= count; i++)
				b.occupied_seats.pop_back();
			flag = 1;
		}
	}
	if (flag == 0)
		throw std::invalid_argument("Error!");
}