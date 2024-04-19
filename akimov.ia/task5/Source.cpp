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

class Cinema
{
public:
    Date date;
    Time time;
    string movieName;
    int hallNumber;
    int baseTicketPrice;
    vector<vector<bool>> seats;

    Cinema(Date d, Time t, string name, int hall, int price, int rows, int seatsPerRow)
        : date(d), time(t), movieName(name), hallNumber(hall), baseTicketPrice(price)
    {
        seats.resize(rows, vector<bool>(seatsPerRow, true));
    }

    int determineBasePrice()
    {
        if (time.hour < 12)
            return baseTicketPrice * 0.75;
        else if (time.hour > 18)
            return baseTicketPrice * 1.5;
        else
            return baseTicketPrice;
    }
};

class TicketOffice
{
private:
    vector<Cinema> cinemas;
public:
    void addCinema(Cinema cinema)
    {
        cinemas.push_back(cinema);
    }

    bool checkAvailability(Cinema& cinema, int row, int seat)
    {
        if (row >= 0 && row < cinema.seats.size() && seat >= 0 && seat < cinema.seats[0].size())
            return cinema.seats[row][seat];
        return false;
    }

    void reserveSeats(Cinema& cinema, int row, int seat)
    {
        if (row >= 0 && row < cinema.seats.size() && seat >= 0 && seat < cinema.seats[0].size())
            cinema.seats[row][seat] = false;
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
                cinema.movieName == movieName && cinema.hallNumber == hallNumber)
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
            cout << "Продажа билетов на этот сеанс не доступна." << endl;
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
        for (int row = 0; row < cinema->seats.size(); ++row)
            for (int seat = 0; seat < cinema->seats[0].size(); ++seat)
                if (checkAvailability(*cinema, row, seat) && numTickets > 0)
                {
                    reserveSeats(*cinema, row, seat);
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
        for (int row = 0; row < cinema->seats.size(); ++row)
            for (int seat = 0; seat < cinema->seats[0].size(); ++seat)
                if (!checkAvailability(*cinema, row, seat) && numCancelledTickets < numTickets)
                {
                    cinema->seats[row][seat] = true;
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
            for (int row = 0; row < cinema->seats.size(); ++row)
                for (int seat = 0; seat < cinema->seats[0].size(); ++seat)
                    if (!checkAvailability(*cinema, row, seat) && numTickets > 0)
                    {
                        cout << "Дата: " << cinema->date.day << "." << cinema->date.month << "." << cinema->date.year << endl;
                        cout << "Время: " << cinema->time.hour << ":" << cinema->time.minute << endl;
                        cout << "Фильм: " << cinema->movieName << endl;
                        cout << "Зал: " << cinema->hallNumber << endl;
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
    Cinema cinema1(Date(22, 4, 2024), Time(9, 20), "Зелёная книга", 1, 200, 10, 10);
    ticketOffice.addCinema(cinema1);
    Cinema cinema2(Date(22, 4, 2024), Time(12, 0), "Один плюс один", 1, 250, 8, 12);
    ticketOffice.addCinema(cinema2);
    Cinema cinema3(Date(22, 4, 2024), Time(19, 40), "Выстрел в пустоту", 1, 200, 10, 10);
    ticketOffice.addCinema(cinema3);
    Cinema cinema4(Date(23, 4, 2024), Time(9, 20), "Sicario", 1, 250, 8, 12);
    ticketOffice.addCinema(cinema4);
    Cinema cinema5(Date(23, 4, 2024), Time(12, 0), "Бесславные ублюдки", 1, 200, 10, 10);
    ticketOffice.addCinema(cinema5);
    Cinema cinema6(Date(23, 4, 2024), Time(19, 40), "Оппенгеймер", 1, 250, 8, 12);
    ticketOffice.addCinema(cinema6);
    Cinema cinema7(Date(25, 4, 2024), Time(9, 20), "Зелёный слоник", 1, 200, 10, 10);
    ticketOffice.addCinema(cinema7);
    Cinema cinema8(Date(25, 4, 2024), Time(12, 0), "Заводной апельсин", 1, 250, 8, 12);
    ticketOffice.addCinema(cinema8);
    Cinema cinema9(Date(28, 4, 2024), Time(19, 40), "Движение вверх", 1, 200, 10, 10);
    ticketOffice.addCinema(cinema9);
    Cinema cinema10(Date(30, 4, 2024), Time(9, 20), "Голос улиц", 1, 250, 8, 12);
    ticketOffice.addCinema(cinema10);
    Date currentDate1(22, 4, 2024); // дата, когда будет фильм
    Time currentTime1(9, 20); // время начала фильма
    ticketOffice.bookTickets(currentDate1, currentTime1, "Зелёная книга", 1, false, 2);
    ticketOffice.printTickets(currentDate1, currentTime1, "Зелёная книга", 1, 2);
    ticketOffice.cancelTickets(currentDate1, currentTime1, "Зелёная книга", 1, 1);
    Date currentDate2(23, 4, 2024);
    Time currentTime2(12, 0);
    ticketOffice.bookTickets(currentDate2, currentTime2, "Бесславные ублюдки", 1, true, 1);
    ticketOffice.printTickets(currentDate2, currentTime2, "Бесславные ублюдки", 1, 1);
    ticketOffice.cancelTickets(currentDate2, currentTime2, "Бесславные ублюдки", 1, 1);
    Date currentDate3(28, 4, 2024);
    Time currentTime3(19, 40);
    ticketOffice.bookTickets(currentDate3, currentTime3, "Движение вверх", 1, true, 2);
    ticketOffice.printTickets(currentDate3, currentTime3, "Движение вверх", 1, 2);
    ticketOffice.cancelTickets(currentDate3, currentTime3, "Движение вверх", 1, 2);
    system("pause");
    return 0;
}
