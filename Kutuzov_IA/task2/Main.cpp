#include "Calendar.h"
#include <iostream>

#define COM_N 4 // Number of commands

typedef void (*CommandFunction) (CCalendar*);


TDate ReceiveDateInput(CCalendar* Calendar,  bool CheckValid);
bool IsNumber(std::string InString);

// Commands
void Com_AddEvent(CCalendar* Calendar);
void Com_RemoveEvent(CCalendar* Calendar);
void Com_OffsetEvent(CCalendar* Calendar);
void Com_DateDifference(CCalendar* Calendar);

// Main
int main()
{
    CCalendar Calendar = CCalendar(30);

    std::string CommandNames[COM_N] = {"Add", "Remove", "Offset", "Diff"};
    CommandFunction Commands[COM_N] = {&Com_AddEvent, &Com_RemoveEvent, &Com_OffsetEvent, &Com_DateDifference};

    bool IsRunning = true;
    while(IsRunning)
    {
        std::string CommandInput;
        std::cout << "Input Command (";
        for (int i = 0; i < COM_N; i++)
            std::cout << CommandNames[i] << ", ";

        std::cout << "Exit): ";

        std::cin >> CommandInput;

        bool Found = false;
        for (int i = 0; i < COM_N; i++)
            if (CommandNames[i] == CommandInput)
            {
                std::cout << std::endl << std::endl;
                Commands[i](&Calendar);
                Found = true;
                break;
            }

        if (CommandInput == "Exit")
            IsRunning = false;

        else if (!Found)
            std::cout << std::endl << "Invalid command!";

        else
            Calendar.PrintEvents();
            
        std::cout << std::endl << std::endl;
    }

    return 0;
}



TDate ReceiveDateInput(CCalendar* Calendar,  bool CheckValid)
{
    TDate Date;

    do
    {
        std::string InDatePart;
        std::string Parts[3] = {"Year", "Month", "Day"};

        for (int i = 0; i < 3; i++)
        {
            do
            {
                std::cout << "Input " << Parts[i] << ": ";
                std::cin >> InDatePart;

                if (!IsNumber(InDatePart))
                    std::cout << std::endl << "Not a number!" << std::endl;

            } while(!IsNumber(InDatePart));


            switch (i)
            {
            case 0: Date.Year = std::stoi(InDatePart);
                break;
                    
            case 1: Date.Month = std::stoi(InDatePart);
                break;

            case 2: Date.Day = std::stoi(InDatePart);
                break;
            }
        }

        if (!Calendar->IsDateValid(Date) && CheckValid)
            std::cout << std::endl << "Invalid Date!" << std::endl;
            
    } while (!Calendar->IsDateValid(Date) && CheckValid);

    return Date;
}


bool IsNumber(std::string InString)
{
    bool Result = true;
    for (int i = 0; i < InString.length(); i++)
        if ( !( std::isdigit(InString.c_str()[i]) || InString.c_str()[i] == '-' ) )
        {
            Result = false;
            break;
        }

    return Result;
}


// Commands
void Com_AddEvent(CCalendar* Calendar)
{
    std::string EventName;
    TDate EventDate;

    std::cout << "Input Event Name: ";
    std::cin >> EventName;
    EventDate = ReceiveDateInput(Calendar, true);

    Calendar->SetEvent(EventDate, EventName);
}

void Com_RemoveEvent(CCalendar* Calendar)
{
    std::string EventName;

    std::cout << "Input Event Name: ";
    std::cin >> EventName;

    Calendar->RemoveEvent(EventName);
}

void Com_OffsetEvent(CCalendar* Calendar)
{
    std::string EventName;
    TDate Offset;

    std::cout << "Input Event Name: ";
    std::cin >> EventName;
    Offset = ReceiveDateInput(Calendar, false);

    Calendar->OffsetEvent(EventName, Offset);
}

void Com_DateDifference(CCalendar* Calendar)
{
    std::string EventName;
    TDate Date_2;

    Date_2 = ReceiveDateInput(Calendar, true);
    std::cout << "Input Event Name: ";
    std::cin >> EventName;
    
    TDate Date_1 = Calendar->GetDate(EventName);

    TDate Diff = Calendar->FindDeltaTime(Date_1, Date_2);
    std::cout << std::endl << "Difference: " << Diff.Day << "." << Diff.Month << "."<< Diff.Year << std::endl;
}