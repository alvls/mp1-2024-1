
//Каждый сеанс описывается датой, временем начала сеанса, названием фильма, номером зала, стоимостью билета в зависимости от зоны(VIP и обычная).
//Для упрощения считать, что покупатель указывает тип зоны и требуемое число билетов, а места выделяются кассой автоматически(при наличии свободных).
//Зрительные места в каждом зале описываются номером ряда и номером в ряду.
//Продажа билетов на сеанс прекращается через 10 минут после начала сеанса.
//Информация о всех сеансах на ближайшие 30 дней проката хранится в классе Кинотеатр.
//Для каждого зала установлена базовая стоимость билетов(на дневные сеансы – от 12.00 до 18.00).
//Стоимость билетов на утренние сеансы(до 12.00) составляет 75 % от базовой, стоимость билетов на вечерние сеансы(после 18.00) – 150 % от базовой.
//Информация о зрительных местах(свободно / занято) в каждом зале на каждом сеансе также хранится в классе Кинотеатр.
// 
//Класс Билетная касса должен предоставлять следующие операции: 
//1) принять данные покупателя : дату, время сеанса, название фильма, номер зала, тип зоны, число мест, 
//2) проверить наличие требуемого количества свободных мест в требуемой зоне, 
//3) зарезервировать требуемое количество мест, 
//4) рассчитать общую стоимость билетов, 
//5) отменить заказ билетов, 
//6) сформировать билеты(каждый билет включает : дату, время сеанса, название фильма, номер зала, номер ряда, номер места в ряду).
#include "TicketOffice.h"
#include <string>
#include <iostream>
#include <ciso646>
TicketOffice::TicketOffice(Cinema& cinema_) : cinema(cinema_) {}
double TicketOffice::buy_tickets(Date date, Time time, std::string name, unsigned hall_number, unsigned seat_type, unsigned count_of_tickets)
{	
	double price;
	Hall* hall_ptr = nullptr;
	for (Hall& a : cinema.halls)
	{
		if (a.hall_number == hall_number)
		{
			hall_ptr = &a;
		}
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
	price = movie_session_ptr->base_cost * count_of_tickets;
	if (seat_type == 1)
		price *= 2;
	if (time.hour < 12)
		price *= 0.75;
	if (time.hour > 18)
		price *= 1.5;
	movie_session_ptr->free_seats -= count_of_tickets;
	return price;

}