#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct Time
{
    int hour;
    int minute;
    Time(int h, int m) : hour(h), minute(m) {}
};

struct Date
{
    int day;
    int month;
    int year;
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
};

class Movie
{
public:
    string name;
    int baseTicketPrice;
    Movie(string n, int price) : name(n), baseTicketPrice(price) {}
};

class Hall
{
public:
    int hallNumber;
    vector<vector<bool>> seats;

    Hall(int number, int rows, int seatsPerRow) : hallNumber(number)
    {
        seats.resize(rows, vector<bool>(seatsPerRow, true));
    }

    bool isSeatAvailable(int row, int seat)
    {
        if (row >= 0 && row < seats.size() && seat >= 0 && seat < seats[0].size())
            return seats[row][seat];
        return false;
    }
    
    void reserveSeat(int row, int seat)
    {
        if (row >= 0 && row < seats.size() && seat >= 0 && seat < seats[0].size())
            seats[row][seat] = false;
    }

    void cancelSeat(int row, int seat)
    {
        if (row >= 0 && row < seats.size() && seat >= 0 && seat < seats[0].size())
            seats[row][seat] = true;
    }
};

class Cinema
{
public:
    Date date;
    Time time;
    Movie movie;
    Hall hall;

    Cinema(Date d, Time t, Movie m, Hall h) : date(d), time(t), movie(m), hall(h) {}

    int determineBasePrice()
    {
        if (time.hour < 12)
            return movie.baseTicketPrice * 0.75;
        else if (time.hour > 18)
            return movie.baseTicketPrice * 1.5;
        else
            return movie.baseTicketPrice;
    }
};

class TicketOffice
{
    vector<Cinema> cinemas;
public:
    void addCinema(Cinema cinema)
    {
        cinemas.push_back(cinema);
    }

    int calculateTotalPrice(Cinema& cinema, int numTickets, bool isVIP)
    {
        int basePrice = cinema.determineBasePrice();
        int totalPrice = basePrice * numTickets;
        if (isVIP)
            totalPrice *= 2;
        return totalPrice;
    }

    Cinema* findCinema(Date date, Time time, string movieName, int hallNumber)
    {
        for (Cinema& cinema : cinemas)
            if (cinema.date.day == date.day && cinema.date.month == date.month && cinema.date.year == date.year &&
                cinema.time.hour == time.hour && cinema.time.minute == time.minute &&
                cinema.movie.name == movieName && cinema.hall.hallNumber == hallNumber)
                return &cinema;
        return nullptr;
    }

    bool bookTickets(Date date, Time time, string movieName, int hallNumber, bool isVIP, int numTickets)
    {
        Cinema* cinema = findCinema(date, time, movieName, hallNumber);
        if (!cinema)
        {
            cout << "Сеанс не найден." << endl;
            return false;
        }
        time_t now = ::time(nullptr);
        tm* currentTime = localtime(&now);
        if (date.day < currentTime->tm_mday ||
            date.month < currentTime->tm_mon + 1 ||
            date.year < currentTime->tm_year + 1900 ||
            date.day > currentTime->tm_mday + 3)
        {
            cout << "Продажа билетов на этот сеанс недоступна." << endl;
            return false;
        }
        int currentTimeInMinutes = time.hour * 60 + time.minute;
        int cinemaTimeInMinutes = cinema->time.hour * 60 + cinema->time.minute;
        if (currentTimeInMinutes > cinemaTimeInMinutes + 10)
        {
            cout << "Продажа билетов на этот сеанс завершена." << endl;
            return false;
        }
        int totalPrice = calculateTotalPrice(*cinema, numTickets, isVIP);
        for (int row = 0; row < cinema->hall.seats.size(); ++row)
            for (int seat = 0; seat < cinema->hall.seats[0].size(); ++seat)
                if (cinema->hall.isSeatAvailable(row, seat) && numTickets > 0)
                {
                    cinema->hall.reserveSeat(row, seat);
                    --numTickets;
                }
        cout << "Билеты успешно забронированы. Общая стоимость: " << totalPrice << " рублей." << endl;
        return true;
    }

    void cancelTickets(Date date, Time time, string movieName, int hallNumber, int numTickets)
    {
        Cinema* cinema = findCinema(date, time, movieName, hallNumber);
        if (!cinema)
        {
            cout << "Сеанс не найден." << endl;
            return;
        }
        int numCancelledTickets = 0;
        for (int row = 0; row < cinema->hall.seats.size(); ++row)
            for (int seat = 0; seat < cinema->hall.seats[0].size(); ++seat)
                if (!cinema->hall.isSeatAvailable(row, seat) && numCancelledTickets < numTickets)
                {
                    cinema->hall.cancelSeat(row, seat);
                    ++numCancelledTickets;
                }
        cout << "Отменено билетов: " << numCancelledTickets << endl << "--------------------" << endl;
    }

    void printTickets(Date date, Time time, string movieName, int hallNumber, int numTickets)
    {
        Cinema* cinema = findCinema(date, time, movieName, hallNumber);
        if (cinema)
        {
            cout << endl << "Билеты:" << endl;
            for (int row = 0; row < cinema->hall.seats.size(); ++row)
                for (int seat = 0; seat < cinema->hall.seats[0].size(); ++seat)
                    if (!cinema->hall.isSeatAvailable(row, seat) && numTickets > 0)
                    {
                        cout << "Дата: " << cinema->date.day << "." << cinema->date.month << "." << cinema->date.year << endl;
                        cout << "Время: " << cinema->time.hour << ":" << cinema->time.minute << endl;
                        cout << "Фильм: " << cinema->movie.name << endl;
                        cout << "Зал: " << cinema->hall.hallNumber << endl;
                        cout << "Ряд: " << row << ", Место: " << seat << endl << endl;
                        --numTickets;
                    }
        }
        else
            cout << "Сеанс не найден." << endl;
    }
};

int main()
{
    system("chcp 1251");
    system("cls");
    TicketOffice ticketOffice;
    Movie movie1("Зелёная книга", 200);
    Movie movie2("Один плюс один", 250);
    Movie movie3("Выстрел в пустоту", 200);
    Movie movie4("Sicario", 250);
    Movie movie5("Бесславные ублюдки", 200);
    Movie movie6("Оппенгеймер", 250);
    Movie movie7("Зелёный слоник", 200);
    Movie movie8("Заводной апельсин", 250);
    Movie movie9("Движение вверх", 200);
    Movie movie10("Голос улиц", 250);
    Hall hall1(1, 10, 10);
    Hall hall2(1, 8, 12);
    Cinema cinema1(Date(22, 5, 2024), Time(9, 20), movie1, hall1);
    ticketOffice.addCinema(cinema1);
    Cinema cinema2(Date(22, 5, 2024), Time(12, 0), movie2, hall2);
    ticketOffice.addCinema(cinema2);
    Cinema cinema3(Date(22, 5, 2024), Time(19, 40), movie3, hall1);
    ticketOffice.addCinema(cinema3);
    Cinema cinema4(Date(23, 5, 2024), Time(9, 20), movie4, hall2);
    ticketOffice.addCinema(cinema4);
    Cinema cinema5(Date(23, 5, 2024), Time(12, 0), movie5, hall1);
    ticketOffice.addCinema(cinema5);
    Cinema cinema6(Date(23, 5, 2024), Time(19, 40), movie6, hall2);
    ticketOffice.addCinema(cinema6);
    Cinema cinema7(Date(25, 5, 2024), Time(9, 20), movie7, hall1);
    ticketOffice.addCinema(cinema7);
    Cinema cinema8(Date(25, 5, 2024), Time(12, 0), movie8, hall2);
    ticketOffice.addCinema(cinema8);
    Cinema cinema9(Date(28, 5, 2024), Time(19, 40), movie9, hall1);
    ticketOffice.addCinema(cinema9);
    Cinema cinema10(Date(30, 5, 2024), Time(9, 20), movie10, hall2);
    ticketOffice.addCinema(cinema10);
    Date currentDate1(22, 5, 2024); // дата, когда будет фильм
    Time currentTime1(9, 20); // время начала фильма
    ticketOffice.bookTickets(currentDate1, currentTime1, "Зелёная книга", 1, false, 2);
    ticketOffice.printTickets(currentDate1, currentTime1, "Зелёная книга", 1, 2);
    ticketOffice.cancelTickets(currentDate1, currentTime1, "Зелёная книга", 1, 1);
    Date currentDate2(23, 5, 2024);
    Time currentTime2(12, 0);
    ticketOffice.bookTickets(currentDate2, currentTime2, "Бесславные ублюдки", 1, true, 1);
    ticketOffice.printTickets(currentDate2, currentTime2, "Бесславные ублюдки", 1, 1);
    ticketOffice.cancelTickets(currentDate2, currentTime2, "Бесславные ублюдки", 1, 1);
    Date currentDate3(28, 5, 2024);
    Time currentTime3(19, 40);
    ticketOffice.bookTickets(currentDate3, currentTime3, "Движение вверх", 1, true, 2);
    ticketOffice.printTickets(currentDate3, currentTime3, "Движение вверх", 1, 2);
    ticketOffice.cancelTickets(currentDate3, currentTime3, "Движение вверх", 1, 2);
    system("pause");
    return 0;
}