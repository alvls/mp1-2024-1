# pragma once
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

    int MaxEvents;

public:
    CCalendar(int InMaxEvents = 100); // Default Constructor
    ~CCalendar(); // Destructor

    // Set event to date
    void SetEvent(TDate Date, std::string Event);

    // Removes an event by it's name or date
    void RemoveEvent(std::string Event);
    void RemoveEvent(TDate& Date);

    // Get event data
    TDate GetDate(std::string Event);

    // Get event at date
    std::string GetEvent(TDate& Date);

    // Checks if the date is free
    bool IsDateFree(TDate& Date);
    
    // Cheks if event exists
    bool IsEventPreset(std::string Event);

    // Finds difference between dates
    TDate FindDeltaTime(TDate& InDate_1, TDate& InDate_2);

    // Offset the selected event
    void OffsetEvent(std::string Event, TDate& Offset);

    // Is leap year
    bool IsLeapYear(int Year);

    // Returns the number of days in any month
    int GetNumberOfDays(int InMonth, int InYear);

    // Checks if the date is valid
    bool IsDateValid(TDate& InDate);

    // Prints out all of the events
    void PrintEvents();

};