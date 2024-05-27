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
    Movie(string n) : name(n) {}
};

class Hall
{
public:
    int hallNumber;
    int baseTicketPrice;
    vector<vector<bool>> seats;

    Hall(int number, int rows, int seatsPerRow, int price) : hallNumber(number), baseTicketPrice(price)
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

class Session // Сеанс
{
public:
    Date date;
    Time time;
    Movie movie;
    Hall& hall;

    Session(Date d, Time t, Movie m, Hall& h) : date(d), time(t), movie(m), hall(h) {}

    int determineBasePrice()
    {
        if (time.hour < 12)
            return hall.baseTicketPrice * 0.75;
        else if (time.hour > 18)
            return hall.baseTicketPrice * 1.5;
        else
            return hall.baseTicketPrice;
    }
};

class Cinema // Кинотеатр
{
public:
    vector<Hall> halls;
    vector<Session> sessions;

    void addHall(Hall hall)
    {
        halls.push_back(hall);
    }

    void addSession(Session session)
    {
        sessions.push_back(session);
    }

    Session* findSession(Date date, Time time, string movieName, int hallNumber)
    {
        for (Session& session : sessions)
            if (session.date.day == date.day && session.date.month == date.month && session.date.year == date.year &&
                session.time.hour == time.hour && session.time.minute == time.minute &&
                session.movie.name == movieName && session.hall.hallNumber == hallNumber)
                return &session;
        return nullptr;
    }
};

class TicketOffice // Касса кинотеатра
{
    Cinema& cinema;
    bool isWithinThreeDays(const Date& date)
    {
        time_t now = time(nullptr);
        tm* currentTime = localtime(&now);
        tm sessionDateTime = { 0 };
        sessionDateTime.tm_year = date.year - 1900;
        sessionDateTime.tm_mon = date.month - 1;
        sessionDateTime.tm_mday = date.day;
        time_t sessionTime = mktime(&sessionDateTime);
        double secondsInThreeDays = 3 * 24 * 60 * 60;
        double timeDiff = difftime(sessionTime, now);
        return timeDiff >= 0 && timeDiff <= secondsInThreeDays;
    }
public:
    TicketOffice(Cinema& c) : cinema(c) {}

    int calculateTotalPrice(Session& session, int numTickets, bool isVIP)
    {
        int basePrice = session.determineBasePrice();
        int totalPrice = basePrice * numTickets;
        if (isVIP)
            totalPrice *= 2;
        return totalPrice;
    }

    bool bookTickets(Date date, Time time, string movieName, int hallNumber, bool isVIP, int numTickets)
    {
        Session* session = cinema.findSession(date, time, movieName, hallNumber);
        if (!session)
        {
            cout << "Сеанс не найден." << endl;
            return false;
        }
        time_t now = ::time(nullptr);
        tm* currentTime = localtime(&now);
        tm sessionDateTime = { 0 };
        sessionDateTime.tm_year = session->date.year - 1900;
        sessionDateTime.tm_mon = session->date.month - 1;
        sessionDateTime.tm_mday = session->date.day;
        sessionDateTime.tm_hour = session->time.hour;
        sessionDateTime.tm_min = session->time.minute;
        time_t sessionTime = mktime(&sessionDateTime);
        if (difftime(sessionTime, now) < -600) // Продажа билетов заканчивается за 10 минут до сеанса
        {
            cout << "Продажа билетов на этот сеанс завершена." << endl;
            return false;
        }
        if (!isWithinThreeDays(date)) // Продажа билетов проводится на сеансы в пределах трех дней от текущей даты
        {
            cout << "Продажа билетов на этот сеанс недоступна." << endl;
            return false;
        }
        int totalPrice = calculateTotalPrice(*session, numTickets, isVIP);
        for (int row = 0; row < session->hall.seats.size(); ++row)
            for (int seat = 0; seat < session->hall.seats[0].size(); ++seat)
                if (session->hall.isSeatAvailable(row, seat) && numTickets > 0)
                {
                    session->hall.reserveSeat(row, seat);
                    --numTickets;
                }
        cout << "Билеты успешно забронированы. Общая стоимость: " << totalPrice << " рублей." << endl;
        return true;
    }

    void cancelTickets(Date date, Time time, string movieName, int hallNumber, int numTickets)
    {
        Session* session = cinema.findSession(date, time, movieName, hallNumber);
        if (!session)
        {
            cout << "Сеанс не найден." << endl;
            return;
        }
        int numCancelledTickets = 0;
        for (int row = 0; row < session->hall.seats.size(); ++row)
            for (int seat = 0; seat < session->hall.seats[0].size(); ++seat)
                if (!session->hall.isSeatAvailable(row, seat) && numCancelledTickets < numTickets)
                {
                    session->hall.cancelSeat(row, seat);
                    ++numCancelledTickets;
                }
        cout << "Отменено билетов: " << numCancelledTickets << endl << "--------------------" << endl;
    }

    void printTickets(Date date, Time time, string movieName, int hallNumber, int numTickets)
    {
        Session* session = cinema.findSession(date, time, movieName, hallNumber);
        if (session)
        {
            cout << endl << "Билеты:" << endl;
            for (int row = 0; row < session->hall.seats.size(); ++row)
                for (int seat = 0; seat < session->hall.seats[0].size(); ++seat)
                    if (!session->hall.isSeatAvailable(row, seat) && numTickets > 0)
                    {
                        cout << "Дата: " << session->date.day << "." << session->date.month << "." << session->date.year << endl;
                        cout << "Время: " << session->time.hour << ":" << session->time.minute << endl;
                        cout << "Фильм: " << session->movie.name << endl;
                        cout << "Зал: " << session->hall.hallNumber << endl;
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
    Cinema cinema;
    Hall hall1(1, 10, 10, 200);
    Hall hall2(2, 8, 12, 250);
    cinema.addHall(hall1);
    cinema.addHall(hall2);
    Movie movie1("Зелёная книга");
    Movie movie2("Один плюс один");
    Movie movie3("Выстрел в пустоту");
    Movie movie4("Sicario");
    Movie movie5("Бесславные ублюдки");
    Movie movie6("Оппенгеймер");
    Movie movie7("Зелёный слоник");
    Movie movie8("Заводной апельсин");
    Movie movie9("Движение вверх");
    Movie movie10("Голос улиц");
    cinema.addSession(Session(Date(22, 5, 2024), Time(9, 20), movie1, hall1));
    cinema.addSession(Session(Date(22, 5, 2024), Time(12, 0), movie2, hall2));
    cinema.addSession(Session(Date(22, 5, 2024), Time(19, 40), movie3, hall1));
    cinema.addSession(Session(Date(23, 5, 2024), Time(9, 20), movie4, hall2));
    cinema.addSession(Session(Date(23, 5, 2024), Time(12, 0), movie5, hall2));
    cinema.addSession(Session(Date(23, 5, 2024), Time(19, 40), movie6, hall2));
    cinema.addSession(Session(Date(25, 5, 2024), Time(9, 20), movie7, hall1));
    cinema.addSession(Session(Date(25, 5, 2024), Time(12, 0), movie8, hall2));
    cinema.addSession(Session(Date(28, 5, 2024), Time(19, 40), movie9, hall1));
    cinema.addSession(Session(Date(30, 5, 2024), Time(9, 20), movie10, hall2));
    TicketOffice ticketOffice(cinema);
    ticketOffice.bookTickets(Date(22, 5, 2024), Time(9, 20), "Зелёная книга", 1, false, 2);
    ticketOffice.printTickets(Date(22, 5, 2024), Time(9, 20), "Зелёная книга", 1, 2);
    ticketOffice.cancelTickets(Date(22, 5, 2024), Time(9, 20), "Зелёная книга", 1, 1);
    ticketOffice.bookTickets(Date(23, 5, 2024), Time(12, 0), "Бесславные ублюдки", 2, true, 1);
    ticketOffice.printTickets(Date(23, 5, 2024), Time(12, 0), "Бесславные ублюдки", 2, 1);
    ticketOffice.cancelTickets(Date(23, 5, 2024), Time(12, 0), "Бесславные ублюдки", 2, 1);
    ticketOffice.bookTickets(Date(28, 5, 2024), Time(19, 40), "Движение вверх", 1, true, 2);
    ticketOffice.printTickets(Date(28, 5, 2024), Time(19, 40), "Движение вверх", 1, 2);
    ticketOffice.cancelTickets(Date(28, 5, 2024), Time(19, 40), "Движение вверх", 1, 2);
    system("pause");
    return 0;
}