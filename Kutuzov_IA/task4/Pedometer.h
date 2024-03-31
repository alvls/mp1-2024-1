#pragma once

#include <map>
#include <string>

enum EWeekDay {Su, Mo, Tu, We, Th, Fr, Sa};

// Date structure
struct TDate
{
	int Year;
	int Month;
	int Day;

public:
	// Consructor
	TDate(int InYear = 1900, int InMonth = 1, int InDay = 1);

	// Returns the day of the week at this date
	EWeekDay GetWeekDay() const;
	
	// Checks if date is valid
	bool IsValidDate();

	bool operator==(const TDate& c) const;
	bool operator>(const TDate& c) const;
	bool operator>=(const TDate& c) const;
	bool operator<(const TDate& c) const;
};


// Time structure
struct TTime
{
	int Hour;
	int Minute;

	// Constructor
	TTime(int InHour = 0, int InMinute = 0);

	// Checks if time is valid
	bool IsValidTime();

	bool operator==(const TTime& c) const;
	bool operator>(const TTime& c) const;
	bool operator<(const TTime& c) const;
};



// Single walking session structure
struct TWalkingSession
{
	TDate Date;
	TTime StartTime;
	TTime EndTime;

	int StepCount;

	TWalkingSession();
	TWalkingSession(const TDate& InDate, const TTime& InStartTime, const TTime& InEndTime, int InStepCount);
};


// Pedometer class
class CPedometer
{
	// Main data structure of the class, to access a record its Date and StartTime are required
	std::map<TDate, std::map<TTime, TWalkingSession>> Records;

	// A formal start date, every earlier record won't be taken into the account
	TDate StartDate;

public:
	CPedometer();

	// Start Date handling
	void SetStartDate(const TDate& InStartDate);
	const TDate& GetStartDate();

	// Creates a walking session record, throws exceptions if something goes wrong
	void CreateRecord(const TDate& Date, const TTime& StartTime, const TTime& EndTime, const int& StepCount);

	// Gets information about the selected record, returns true if successful
	bool GetRecord(TWalkingSession& Out_Record, const TDate& Date, const TTime& StartTime);

	// Average step count values
	int GetAllTimeAverage();
	int GetMonthAverage(int Month, int Year);
	int GetAllTimeWeekDayAverage(EWeekDay WeekDay);
	
	// Max step count value
	int GetAllTimeDailyMaximum(TDate& Out_RecordDate);
	int GetMonthDailyMaximum(TDate& Out_RecordDate, int Month, int Year);

	// Saving / Loading
	void SaveToFile(std::string FileName);
	void LoadFromFile(std::string FileName);

	// Debugging
	void Print();
};
