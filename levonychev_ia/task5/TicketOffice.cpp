
//������ ����� ����������� �����, �������� ������ ������, ��������� ������, ������� ����, ���������� ������ � ����������� �� ����(VIP � �������).
//��� ��������� �������, ��� ���������� ��������� ��� ���� � ��������� ����� �������, � ����� ���������� ������ �������������(��� ������� ���������).
//���������� ����� � ������ ���� ����������� ������� ���� � ������� � ����.
//������� ������� �� ����� ������������ ����� 10 ����� ����� ������ ������.
//���������� � ���� ������� �� ��������� 30 ���� ������� �������� � ������ ���������.
//��� ������� ���� ����������� ������� ��������� �������(�� ������� ������ � �� 12.00 �� 18.00).
//��������� ������� �� �������� ������(�� 12.00) ���������� 75 % �� �������, ��������� ������� �� �������� ������(����� 18.00) � 150 % �� �������.
//���������� � ���������� ������(�������� / ������) � ������ ���� �� ������ ������ ����� �������� � ������ ���������.
// 
//����� �������� ����� ������ ������������� ��������� ��������: 
//1) ������� ������ ���������� : ����, ����� ������, �������� ������, ����� ����, ��� ����, ����� ����, 
//2) ��������� ������� ���������� ���������� ��������� ���� � ��������� ����, 
//3) ��������������� ��������� ���������� ����, 
//4) ���������� ����� ��������� �������, 
//5) �������� ����� �������, 
//6) ������������ ������(������ ����� �������� : ����, ����� ������, �������� ������, ����� ����, ����� ����, ����� ����� � ����).
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