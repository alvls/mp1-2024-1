#define _CRT_SECURE_NO_WARNINGS

#include "Pedometer.h"
#include <ctime>
#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;


// Date structure
TDate::TDate(int InYear, int InMonth, int InDay)
{
	Year = InYear; Month = InMonth; Day = InDay;
}

// Returns the day of the week at this date
EWeekDay TDate::GetWeekDay() const
{
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	int nYear = Year - Month < 3;
	return EWeekDay((Year + Year / 4 - Year / 100 + Year / 400 + t[Month - 1] + Day) % 7);
	
}

// Checks if date is valid
bool TDate::IsValidDate()
{
	int DayNums[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	return (Month > 0 && Month < 13) && (Day > 0 && Day <= DayNums[Month - 1]);
}

bool TDate::operator==(const TDate& c) const
{
	return (Year == c.Year) && (Month == c.Month) && (Day == c.Day);
}

bool TDate::operator>(const TDate& c) const
{
	return (Year > c.Year) || (Year == c.Year) && (Month > c.Month) || (Year == c.Year) && (Month == c.Month) && (Day > c.Day);
}

bool TDate::operator>=(const TDate& c) const
{
	return *this > c || *this == c;
}

bool TDate::operator<(const TDate& c) const
{
	return (Year < c.Year) || (Year == c.Year) && (Month < c.Month) || (Year == c.Year) && (Month == c.Month) && (Day < c.Day);
}



// Time structure
TTime::TTime(int InHour, int InMinute)
{
	Hour = InHour; Minute = InMinute;
}

// Checks if time is valid
bool TTime::IsValidTime()
{
	return (Hour >= 0 && Hour < 24) && (Minute >= 0 && Minute < 60);
}

bool TTime::operator==(const TTime& c) const
{
	return (Hour == c.Hour) && (Minute == c.Minute);
}

bool TTime::operator>(const TTime& c) const
{
	return (Hour > c.Hour) || (Hour == c.Hour) && (Minute > c.Hour);
}

bool TTime::operator<(const TTime& c) const
{
	return (Hour < c.Hour) || (Hour == c.Hour) && (Minute < c.Hour);
}



// Single walking session structure

TWalkingSession::TWalkingSession()
{
	Date = TDate();
	StartTime = TTime(); EndTime = TTime();
	StepCount = 0;
}

TWalkingSession::TWalkingSession(const TDate& InDate, const TTime& InStartTime, const TTime& InEndTime, int InStepCount)
{
	Date = InDate;  StartTime = InStartTime; EndTime = InEndTime; StepCount = InStepCount;
}



// Pedometer
CPedometer::CPedometer() 
{
	StartDate = TDate();
}

// Start Date handling
void CPedometer::SetStartDate(const TDate& InStartDate)
{
	StartDate = InStartDate;
}

const TDate& CPedometer::GetStartDate()
{
	return StartDate;
}

// Creates a walking session record
void CPedometer::CreateRecord(const TDate& Date, const TTime& StartTime, const TTime& EndTime, const int& StepCount)
{
	if (Records.count(Date))
	{
		bool Failed = false;
		for (const auto& Record : Records[Date])
			if ((StartTime > Record.first && Record.second.EndTime > StartTime) || StartTime == Record.first)
			{
				Failed = true;
				break;
			}

		if (Failed)
			throw (exception("This time is already occupied by another record!"));
	}

	if (StartTime > EndTime)
		throw (exception("Invalid sequence of events! Space and Time anomalies are not allowed!"));

	Records[Date][StartTime] = TWalkingSession(Date, StartTime, EndTime, StepCount);
}

// Gets information about the selected record, returns true if successful
bool CPedometer::GetRecord(TWalkingSession& Out_Record, const TDate& Date, const TTime& StartTime)
{
	if (Records.count(Date) && Records[Date].count(StartTime))
	{
		Out_Record = Records[Date][StartTime];
		return true;
	}

	return false;
}

// Average step count values
int CPedometer::GetAllTimeAverage()
{
	int StepCount = 0;
	int RecordCount = 0;

	for (const auto& Date : Records)
		if (Date.first >= StartDate)
			for (const auto& Record : Date.second)
			{
				StepCount += Record.second.StepCount;
				RecordCount++;
			}

	return RecordCount > 0 ? StepCount / RecordCount : 0;
}

int CPedometer::GetMonthAverage(int Month, int Year)
{
	int StepCount = 0;
	int RecordCount = 0;

	for (const auto& Date : Records)
		if (Date.first >= StartDate && Date.first.Year == Year && Date.first.Month == Month)
			for (const auto& Record : Date.second)
			{
				StepCount += Record.second.StepCount;
				RecordCount++;
			}

	return RecordCount > 0 ? StepCount / RecordCount : 0;
}

int CPedometer::GetAllTimeWeekDayAverage(EWeekDay WeekDay)
{
	int StepCount = 0;
	int RecordCount = 0;

	for (const auto& Date : Records)
		if (Date.first >= StartDate && Date.first.GetWeekDay() == WeekDay)
			for (const auto& Record : Date.second)
			{
				StepCount += Record.second.StepCount;
				RecordCount++;
			}

	return RecordCount > 0 ? StepCount / RecordCount : 0;
}

// Max step count value
int CPedometer::GetAllTimeDailyMaximum(TDate& Out_RecordDate)
{
	int StepMax = 0;
	
	for (const auto& Date : Records)
		if (Date.first >= StartDate)
		{
			int Sum = 0;
			for (const auto& Record : Date.second)
				Sum += Record.second.StepCount;

			if (StepMax < Sum)
			{
				StepMax = Sum;
				Out_RecordDate = Date.first;
			}
		}

	return StepMax;
}


int CPedometer::GetMonthDailyMaximum(TDate& Out_RecordDate, int Month, int Year)
{
	int StepMax = 0;

	for (const auto& Date : Records)
		if (Date.first >= StartDate && Date.first.Year == Year && Date.first.Month == Month)
		{
			int Sum = 0;
			for (const auto& Record : Date.second)
				Sum += Record.second.StepCount;

			if (StepMax < Sum)
			{
				StepMax = Sum;
				Out_RecordDate = Date.first;
			}
		}

	return StepMax;
}

// Saving / Loading
void CPedometer::SaveToFile(string FileName)
{
	ofstream file(FileName);

	file << StartDate.Year << " " << StartDate.Month << " " << StartDate.Day << endl;
	file << Records.size() << endl;

	for (const auto& Date : Records)
	{
		file << Date.first.Year << " " << Date.first.Month << " " << Date.first.Day << endl;
		file << Date.second.size() << endl;

		for (const auto& Record : Date.second)
		{
			const TWalkingSession& WSession= Record.second;
			
			file << WSession.StartTime.Hour << " " << WSession.StartTime.Minute << " " << WSession.EndTime.Hour << " " << WSession.EndTime.Minute << " " << WSession.StepCount << endl;
		}
	}

	file.close();
}

void CPedometer::LoadFromFile(string FileName)
{
	ifstream file(FileName);

	if (file.is_open())
	{
		Records.clear();

		int SYear, SMonth, SDay;
		file >> SYear >> SMonth >> SDay;
		StartDate = TDate(SYear, SMonth, SDay);

		int NumRecords = 0;
		file >> NumRecords;

		for (int i = 0; i < NumRecords; i++)
		{
			int Year, Month, Day;
			file >> Year >> Month >> Day;
			TDate Date(Year, Month, Day);

			int NumDateRecords = 0;
			map<TTime, TWalkingSession> DateRecords;

			file >> NumDateRecords;

			for (int j = 0; j < NumDateRecords; j++)
			{
				int SHour, SMinute, EHour, EMinute, StepCount;
				file >> SHour >> SMinute >> EHour >> EMinute >> StepCount;

				TTime StartTime(SHour, SMinute);
				TTime EndTime(EHour, EMinute);

				DateRecords[StartTime] = TWalkingSession(Date, StartTime, EndTime, StepCount);
			}

			Records[Date] = DateRecords;
		}
		file.close();
	}

	else
		throw(exception("No such file!"));
}


// Debugging
void CPedometer::Print()
{
	cout << endl;
	cout << "==========================================================================================" << endl;

	cout << "Starting date: " << StartDate.Day << "." << StartDate.Month << "." << StartDate.Year << endl << endl;

	for (const auto& Date : Records)
		for (const auto& Record : Date.second)
		{
			const TWalkingSession& WSession = Record.second;

			cout << Date.first.Day << "." << Date.first.Month << "." << Date.first.Year << " : " << WSession.StartTime.Hour << "h:" << WSession.StartTime.Minute << "m - " << WSession.EndTime.Hour << "h:" << WSession.EndTime.Minute << "m : " << WSession.StepCount << " Steps;" << endl;
		}

	cout << "==========================================================================================";
	cout << endl;
}