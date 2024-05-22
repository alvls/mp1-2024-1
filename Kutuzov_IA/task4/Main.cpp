#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Pedometer.h"
#include <string>

#define COM_NUM 6

using namespace std;

typedef void (*CommandFunction) (CPedometer*);

// Commands
void Com_SetStart(CPedometer* Pedometer);
void Com_Add(CPedometer* Pedometer);
void Com_Avg(CPedometer* Pedometer);
void Com_Max(CPedometer* Pedometer);
void Com_Save(CPedometer* Pedometer);
void Com_Load(CPedometer* Pedometer);

// Other functions
TDate ReceiveDateInput();
TTime ReceiveTimeInput();
int ReceiveIntInput(string Message);

bool IsInt(string InString);



int main()
{
	CPedometer Pedometer = CPedometer();

	std::string CommandNames[COM_NUM] = { "Set_Start", "Add", "Average", "Max", "Save", "Load"};
	CommandFunction Commands[COM_NUM] = { &Com_SetStart, &Com_Add, &Com_Avg, &Com_Max, &Com_Save, &Com_Load };

	bool Running = true;

	while (Running)
	{
		string Command;
		int CommandID;
		bool Inputing;

		do
		{
			cout << endl << "Input Command (Set_Start, Add, Average, Max, Save, Load, Exit): ";

			cin >> Command;
			Inputing = true;

			for (int i = 0; i < COM_NUM; i++)
				if (Command == CommandNames[i])
				{
					CommandID = i;
					Inputing = false;
					break;
				}


			if (Inputing)
				if (Command == "Exit")
				{
					Running = false;
					Inputing = false;
				}
				else
					cout << "Invalid Command!" << endl << endl;

		} while (Inputing);


		cout << endl;
		if (Running)
			Commands[CommandID](&Pedometer);
	}

	return 0;
}



// Commands

void Com_SetStart(CPedometer* Pedometer)
{
	cout << "Set starting date:" << endl;
	TDate NewStartDate = ReceiveDateInput();

	Pedometer->SetStartDate(NewStartDate);
	Pedometer->Print();
}

void Com_Add(CPedometer* Pedometer)
{
	TDate Date = ReceiveDateInput();
	cout << "Start Time:" << endl;
	TTime StartTime = ReceiveTimeInput();
	cout << "End Time:" << endl;
	TTime EndTime = ReceiveTimeInput();

	int StepCount = 0;

	bool Inputing = true;
	do
	{
		StepCount = ReceiveIntInput("Input Step Count: ");
		Inputing = StepCount < 0;

		if (Inputing)
			cout << endl << "Invalid Step Count!" << endl;

	} while (Inputing);

	try
	{
		Pedometer->CreateRecord(Date, StartTime, EndTime, StepCount);

		Pedometer->Print();
	}

	catch (exception c)
	{
		cout << endl << c.what() << endl;
	}
}

void Com_Avg(CPedometer* Pedometer)
{
	cout << "Choose averge value mode:" << endl << "1. All time average " << endl << "2. Month average " << endl << "3. All time week day average " << endl << endl;
	
	int Mode = 0;
	bool Inputing = true;
	do
	{
		Mode = ReceiveIntInput("Input Mode ID (1 - 3): ");
		Inputing = !(Mode > 0 && Mode < 4);

		if (Inputing)
			cout << endl << "Invalid Mode!" << endl;

	} while (Inputing);

	if (Mode == 1)
	{
		cout << endl << "All Time Average: " << Pedometer->GetAllTimeAverage() << endl;
	}

	else if (Mode == 2)
	{
		cout << endl << "Choose year and month you are interested in:" << endl;
		int Year = 0;
		int Month = 0;
		
		Year = ReceiveIntInput("Input Year: ");

		do
		{
			Month = ReceiveIntInput("Input Month: ");
			Inputing = !(Month > 0 && Month < 13);

			if (Inputing)
				cout << endl << "Invalid Month!" << endl;

		} while (Inputing);


		cout << endl << "Average at chosen month: " << Pedometer->GetMonthAverage(Month, Year) << endl;
	}

	else if (Mode == 3)
	{
		EWeekDay WeekDay;
		do
		{
			int iWeekDay = ReceiveIntInput("Input weekday num (1 - 7): ");
			Inputing = !(iWeekDay > 0 && iWeekDay < 8);

			WeekDay = EWeekDay(iWeekDay % 7);

			if (Inputing)
				cout << endl << "Invalid weedday!" << endl;

		} while (Inputing);

		cout << endl << "Average at chosen weekday: " << Pedometer->GetAllTimeWeekDayAverage(WeekDay) << endl;
	}
}

void Com_Max(CPedometer* Pedometer)
{
	cout << "Choose max value mode:" << endl << "1. All time daily maximum " << endl << "2. Month daily maximum " << endl << endl;

	int Mode = 0;
	bool Inputing = true;
	do
	{
		Mode = ReceiveIntInput("Input Mode ID (1 - 2): ");
		Inputing = !(Mode > 0 && Mode < 3);

		if (Inputing)
			cout << endl << "Invalid Mode!" << endl;

	} while (Inputing);

	if (Mode == 1)
	{
		TDate Date;
		int Value = Pedometer->GetAllTimeDailyMaximum(Date);
		
		cout << endl << "All time daily maximum: " << Value << " at " << Date.Day << "." << Date.Month << "." << Date.Year << endl;
	}

	else if (Mode == 2)
	{
		cout << endl << "Choose year and month you are interested in:" << endl;
		int Year = 0;
		int Month = 0;

		Year = ReceiveIntInput("Input Year: ");

		do
		{
			Month = ReceiveIntInput("Input Month: ");
			Inputing = !(Month > 0 && Month < 13);

			if (Inputing)
				cout << endl << "Invalid Month!" << endl;

		} while (Inputing);

		TDate Date;
		int Value = Pedometer->GetMonthDailyMaximum(Date, Month, Year);
		cout << endl << "Chosen month's daily maximum: " << Value << " at " << Date.Day << "." << Date.Month << "." << Date.Year << endl;
	}
}

void Com_Save(CPedometer* Pedometer)
{
	cout << "Saving to file" << endl << "Input file name (no .txt required): ";
	string FileName;
	cin >> FileName;
	FileName += ".txt";

	Pedometer->SaveToFile(FileName);

	cout << "Data saved to file: " << FileName << endl << endl;
}

void Com_Load(CPedometer* Pedometer)
{
	cout << "Loading file" << endl << "Input file name (no .txt required): ";
	string FileName;
	cin >> FileName;
	FileName += ".txt";

	try
	{
		Pedometer->LoadFromFile(FileName);
		cout << "Data loaded from file: " << FileName << endl;

		Pedometer->Print();
	}

	catch (exception c)
	{
		cout << endl << c.what() << endl;
	}
}



// Other Functions
TDate ReceiveDateInput()
{
	TDate Date = TDate();

	bool Inputing = true;
	do
	{
		cout << "Input Date (DD MM YYYY): ";
		string Day, Month, Year;
		cin >> Day >> Month >> Year;

		if (IsInt(Day) && IsInt(Month) && IsInt(Year))
		{
			Date = TDate(stoi(Year), stoi(Month), stoi(Day));
			Inputing = !Date.IsValidDate();
		}

		else
			Inputing = true;

		if (Inputing)
			cout << endl << "Invalid Date!" << endl;

	} while (Inputing);

	return Date;
}

TTime ReceiveTimeInput()
{
	TTime Time = TTime();

	bool Inputing = true;
	do
	{
		cout << "Input Time (HH MM): ";
		string Hour, Minute;
		cin >> Hour >> Minute;

		if (IsInt(Hour) && IsInt(Minute))
		{
			Time = TTime(stoi(Hour), stoi(Minute));
			Inputing = !Time.IsValidTime();
		}

		else
			Inputing = true;

		if (Inputing)
			cout << endl << "Invalid Time!" << endl;

	} while (Inputing);

	return Time;
}

bool IsInt(string InString)
{
	bool Result = true;
	for (int i = 0; i < InString.length(); i++)
		if (!(isdigit(InString.c_str()[i]) || InString.c_str()[i] == '-'))
		{
			Result = false;
			break;
		}

	return Result;
}


int ReceiveIntInput(string Message)
{
	bool Inputing = true;

	int Result = 0;

	do
	{
		cout << Message;
		string sInt;
		cin >> sInt;
		
		Inputing = !IsInt(sInt);

		if (Inputing)
			cout << endl << "Not a number!" << endl;

		else
			Result = stoi(sInt);

	} while (Inputing);

	return Result;
}