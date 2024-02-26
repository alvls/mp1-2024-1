# pragma once
#include <iostream>
#include <string>

// Date date type
struct TDate
{
    int Year, Month, Day; // Main Data

    TDate(int InYear = 0, int InMonth = 0, int InDay = 0); // Constructor

    bool operator== (const TDate& DateArg); // == operator overload
};


// Calendar class
class CCalendar
{
    TDate* EventDates;
    std::string* Events;

    int MaxEvents = 100;

public:
    CCalendar(); // Default Constructor

    // Set event to date
    void SetEvent(TDate Date, std::string Event);

    // Removes an event by it's name or date
    void RemoveEvent(std::string Event);
    void RemoveEvent(TDate Date);

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