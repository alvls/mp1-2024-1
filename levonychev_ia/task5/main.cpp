
//�������, ��� ������� ������� ���������� �� ������ � �������� ���� ���� �� ������� ����.


//������� ������� �� ����� ������������ ����� 10 ����� ����� ������ ������.

//����� �������� ����� ������ ������������� ��������� ��������: 
//2) ��������� ������� ���������� ���������� ��������� ���� � ��������� ����, 

#include <iostream>
#include <ciso646>
#include "Cinema.h"
#include "TicketOffice.h"
int main()
{
    using namespace std;
    Cinema cinema;
    Hall hall1(1, 15, 15);
    Hall hall2(2, 14, 10);
    MovieSession movie_session1({ 22, 4, 2024 }, { 18, 0 }, "Avatar", hall2, 250);
    MovieSession movie_session2({ 22, 4, 2024 }, { 23, 15 }, "Catch me if you can", hall2, 300);
    cinema.add_hall(hall1);
    cinema.add_hall(hall2);
    cinema.add_movie_session({ 22, 4, 2024 }, { 18, 0 }, "Avatar", hall2, 250);
    cinema.add_movie_session({ 22, 4, 2024 }, { 23, 15 }, "Catch me if you can", hall2, 300);
    //cinema.info();

    TicketOffice ticket_office(cinema);

    //double price1 = ticket_office.buy_tickets({ 22, 4, 2024 }, { 23, 15 }, "Catch me if you can", 2, 0, 2);
    //double price2 = ticket_office.buy_tickets({22, 4, 2024}, {18, 0}, "Avatar", 2, 0, 9);
    //double price3 = ticket_office.buy_tickets({ 22, 4, 2024 }, { 18, 0 }, "Avatar", 2, 0, 2);
    double price4 = ticket_office.buy_tickets({ 22, 4, 2024 }, { 18, 0 }, "Avatar", 2, 0, 5);
    system("pause");
    return 0;
}


