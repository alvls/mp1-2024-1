#include "Calendar.h"

 TDate::TDate(int InYear = 0, int InMonth = 0, int InDay = 0)
 {
    Year = InYear;
    Month = InMonth;
    Day = InDay;
 }

 bool TDate::operator== (const TDate& DateArg)
 {
    return (Year == DateArg.Year && Month == DateArg.Month && Day == DateArg.Day);
 }


CCalendar::CCalendar()
{
    EventDates = new TDate[MaxEvents];
    Events = new std::string[MaxEvents];

}

// Set event to date
void CCalendar::SetEvent(TDate Date, std::string Event)
{
    int i = 0;
    while (!(EventDates[i] == TDate() || EventDates[i] == Date))
        i++;

    if (i >= MaxEvents)
    {
        std::cout << "Can't add more events";
        return;
    }

    EventDates[i] = Date;
    Events[i] = Event;
}

// Get event data
TDate CCalendar::GetDate(std::string Event)
{
    for (int i = 0; i < MaxEvents; i++)
        if (Events[i] == Event)
            return EventDates[i];

    std::cout << "No such event!";
    return TDate();
}

// Get event at date
std::string CCalendar::GetEvent(TDate Date)
{
    for (int i = 0; i < MaxEvents; i++)
        if (EventDates[i] == Date)
            return Events[i];

    std::cout << "No such event!";
    return std::string();
}


// Finds difference between dates
TDate CCalendar::FindDeltaTime(TDate Date_1, TDate Date_2)
{
    if (Date_1.Year > Date_2.Year || Date_1.Month > Date_2.Month || Date_1.Day > Date_2.Day)
    {
        TDate buffer = Date_2;
        Date_2 = Date_1;
        Date_1 = buffer;
    }



}

// Is leap year
bool CCalendar::IsLeapYear(int Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}


// Prints out all of the events
void CCalendar::PrintEvents()
{
    for (int i = 0; i < MaxEvents; i++)
        if ( !( EventDates[i] == TDate() ) )
            std::cout << std::endl << EventDates[i].Year << EventDates[i].Month << EventDates[i].Day;
}
