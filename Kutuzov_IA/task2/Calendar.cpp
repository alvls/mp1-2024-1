#include "Calendar.h"
#include <iostream>

// TDate methods
 TDate::TDate(int InYear, int InMonth, int InDay)
 {
    Year = InYear;
    Month = InMonth;
    Day = InDay;
 }

 bool TDate::operator== (const TDate& DateArg)
 {
    return (Year == DateArg.Year && Month == DateArg.Month && Day == DateArg.Day);
 }


// CCalendar methods
// Constructor
CCalendar::CCalendar(int InMaxEvents)
{
    MaxEvents = InMaxEvents;
    EventDates = new TDate[MaxEvents];
    Events = new std::string[MaxEvents];
}

// Destructor
CCalendar::~CCalendar()
{
    delete[] EventDates;
    delete[] Events;
}

// Set event to date
void CCalendar::SetEvent(TDate Date, std::string Event)
{
    if (IsDateValid(Date))
    {
        int i = 0;
        while (!(EventDates[i] == TDate() || EventDates[i] == Date))
            i++;

        if (i >= MaxEvents)
        {
            std::cout << std::endl << "Can't add more events" << std::endl;
            return;
        }

        EventDates[i] = Date;
        Events[i] = Event;
    }

    else
        std::cout << std::endl << "Invalid date!" << std::endl;
}

// Removes an event by it's name or date
void CCalendar::RemoveEvent(std::string Event)
{
    for (int i = 0; i < MaxEvents; i++)
        if (Events[i] == Event)
        {
            EventDates[i] = TDate();
            return;
        }
    
    std::cout << std::endl << "No such event!" << std::endl;
}

void CCalendar::RemoveEvent(TDate& Date)
{
    if (IsDateValid(Date))
    {
        for (int i = 0; i < MaxEvents; i++)
            if (EventDates[i] == Date)
            {
                EventDates[i] = TDate();
                return;
            }
        
        std::cout << std::endl << "No event planned for this date!" << std::endl;
    }

    else
        std::cout << std::endl << "Invalid date!" << std::endl;
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
std::string CCalendar::GetEvent(TDate& Date)
{
    for (int i = 0; i < MaxEvents; i++)
        if (EventDates[i] == Date)
            return Events[i];

    std::cout <<std::endl << "No such event!" << std::endl;
    return std::string();
}

// Checks if the date is free
bool CCalendar::IsDateFree(TDate& Date)
{
    for (int i = 0; i < MaxEvents; i++)
        if (EventDates[i] == Date)
            return false;
    return true;
}

// Cheks if event exists
bool CCalendar::IsEventPreset(std::string Event)
{
    for (int i = 0; i < MaxEvents; i++)
        if (Events[i] == Event)
            return true;

    return false;
}

// Finds difference between dates
TDate CCalendar::FindDeltaTime(TDate& InDate_1, TDate& InDate_2)
{
    TDate Date_1 = InDate_1;
    TDate Date_2 = InDate_2;

    if (Date_1.Year > Date_2.Year || (Date_1.Year == Date_2.Year && Date_1.Month > Date_2.Month) || ((Date_1.Year == Date_2.Year && Date_1.Month == Date_2.Month) && Date_1.Day > Date_2.Day))
    {
        Date_2 = InDate_1;
        Date_1 = InDate_2;
    }

    TDate Delta = TDate(Date_2.Year - Date_1.Year, Date_2.Month - Date_1.Month, Date_2.Day - Date_1.Day);

    while (Delta.Month < 0 || Delta.Day < 0)
    {
        if (Delta.Month < 0)
        {
            Delta.Year--;
            Delta.Month = Delta.Month + 12;
        }

        if (Delta.Day < 0)
        {
            Delta.Month--;
            Delta.Day = GetNumberOfDays(Date_1.Month, Date_2.Year) - Date_1.Day + Date_2.Day;
        }
    }

    return Delta;
}

// Offset the selected event
void CCalendar::OffsetEvent(std::string Event, TDate& Offset)
{
    int EventID = -1;
    for (int i = 0; i < MaxEvents; i++)
        if (Events[i] == Event)
        {
            EventID = i;
            break;
        }

    if (EventID == -1)
    {
        std::cout << std::endl << "No such event!" << std::endl;
        return;
    }

    TDate NewEventDate = TDate(EventDates[EventID].Year + Offset.Year, EventDates[EventID].Month + Offset.Month, EventDates[EventID].Day + Offset.Day);

    while (!IsDateValid(NewEventDate))
    {
        while (NewEventDate.Month > 12)
        {
            NewEventDate.Year++;
            NewEventDate.Month -= 12;
        }
        while (NewEventDate.Month <= 0)
        {
            NewEventDate.Year--;
            NewEventDate.Month = 12 + NewEventDate.Month;
        }

        while (NewEventDate.Day > GetNumberOfDays(NewEventDate.Month, NewEventDate.Year))
        {
            NewEventDate.Month++;
            NewEventDate.Day -= GetNumberOfDays(NewEventDate.Month, NewEventDate.Year);
        }
        while (NewEventDate.Day <= 0)
        {
            NewEventDate.Month--;
            NewEventDate.Day = GetNumberOfDays(NewEventDate.Month, NewEventDate.Year) + NewEventDate.Day;
        }
    }

    if (IsDateFree(NewEventDate))
        EventDates[EventID] = NewEventDate;

    else
        std::cout << std::endl << "Date occupied!" << std::endl;
    
}

// Is leap year
bool CCalendar::IsLeapYear(int Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

// Returns the number of days in any month
int CCalendar::GetNumberOfDays(int InMonth, int InYear)
{
    int Data[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (InMonth != 2 || IsLeapYear(InYear))
        return Data[InMonth - 1];

    return 28;
}

// Checks if the date is valid
bool CCalendar::IsDateValid(TDate& InDate)
{
    return (InDate.Month > 0 && InDate.Month < 13) && (InDate.Day > 0 && InDate.Day < GetNumberOfDays(InDate.Month, InDate.Year));
}

// Prints out all of the events
void CCalendar::PrintEvents()
{
    std::cout << std::endl << "============================================================" << std::endl << "CALENDAR EVENTS:" << std::endl;
    for (int i = 0; i < MaxEvents; i++)
        if ( !( EventDates[i] == TDate() ) )
            std::cout << std::endl << EventDates[i].Day << "." << EventDates[i].Month << "." << EventDates[i].Year << " : " << Events[i];
}
