# pragma once
#include <iostream>
#include <map>
#include <string>

struct TDate
{
    int Year, Month, Day;

    TDate(int InYear = 0, int InMonth = 0, int InDay = 0);
    
    bool operator== (const TDate& DateArg);
};

class CCalendar
{
    //std::map<TDate, std::string> Events;

    TDate* EventDates;
    std::string* Events;

    int MaxEvents = 100;

public:
    CCalendar(); // Default Constructor

    // Set event to date
    void SetEvent(TDate Date, std::string Event);

    // Get event data
    TDate GetDate(std::string Event);

    // Get event at date
    std::string GetEvent(TDate Date);

    // Finds difference between dates
    TDate FindDeltaTime(TDate Date_1, TDate Date_2);

    // Is leap year
    bool IsLeapYear(int Year);

    // Prints out all of the events
    void PrintEvents();

};