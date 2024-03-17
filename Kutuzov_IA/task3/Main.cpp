#include "Tabulator.h"
#include <string>
#include <iostream>

using namespace std;

typedef void (*CommandFunction) (CTabulator*);



void Com_Tabulate(CTabulator* Tabulator);
void Com_Save(CTabulator* Tabulator);
void Com_Load(CTabulator* Tabulator);

bool IsInt(string InString);
bool IsDouble(string InString);


int main()
{
	std::string CommandNames[3] = { "Tabulate", "Save", "Load"};
	CommandFunction Commands[3] = {  &Com_Tabulate, &Com_Save, &Com_Load};


	bool Running = true;

	CTabulator Tabulator = CTabulator();

	while (Running)
	{
		string Command;
		int CommandID;
		bool Inputing;

		do
		{
			cout << endl << "Input Command (Tabulate, Save, Load, Exit): ";

			cin >> Command;
			Inputing = true;

			for (int i = 0; i < 3; i++)
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
			Commands[CommandID](&Tabulator);

	}

	return 0;
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

bool IsDouble(string InString)
{
	bool Result = true;
	for (int i = 0; i < InString.length(); i++)
		if (!(isdigit(InString.c_str()[i]) || InString.c_str()[i] == '-' || InString.c_str()[i] == '.'))
		{
			Result = false;
			break;
		}

	return Result;
}



void Com_Tabulate(CTabulator* Tabulator)
{
	bool Inputing = true;
	string Input;

	Tabulator->ReInit(); // Resets tabulator

	// Inputting Function 
	do
	{
		cout << "Input Function ID (0 - Sin, 1 - Cos, 2 - Tg, 3 - ArcSin, 4 - ArcCos, 5 - ArcTg, 6 - Log, 7 - Abs): ";
		cin >> Input;

		Inputing = !(IsInt(Input) && stoi(Input) >= 0 && stoi(Input) < NUM_FUNCTIONS);

		if (Inputing)
			cout << "Invalid function ID!" << endl << endl;

	} while (Inputing);

	Tabulator->SetFunction(stoi(Input));


	// Inputting Number of points 
	do
	{
		cout << "Input Number of points: ";
		cin >> Input;

		Inputing = !(IsInt(Input) && stoi(Input) > 0);

		if (Inputing)
			cout << "Invalid number of points!" << endl << endl;

	} while (Inputing);

	Tabulator->SetNumPoints(stoi(Input));


	// Inputting Min / Max
	double Min = 0;
	double Max = 0;


	do
	{
		cout << "Input Starting Value: ";
		cin >> Input;

		Inputing = !IsDouble(Input);

		if (Inputing)
			cout << "Invalid starting value!" << endl << endl;

	} while (Inputing);

	Min = stod(Input);
	
	do
	{
		cout << "Input End Value: ";
		cin >> Input;

		Inputing = !(IsDouble(Input) && stod(Input) > Min);

		if (Inputing)
			cout << "Invalid end value!" << endl << endl;

	} while (Inputing);

	Max = stod(Input);

	Tabulator->SetRange(Min, Max);


	cout << endl << "TABULATION" << endl;
	Tabulator->Tabulate();
	Tabulator->PrintTabulationResult();

}

void Com_Save(CTabulator* Tabulator)
{
	string FileName;
	cout << "Input file name/path (no file type required): ";
	cin >> FileName;
	FileName += ".txt";

	if (Tabulator->SaveResultToFile(FileName))
		cout << "Saved result to file " << "'" << FileName << "'" << endl;

	else
		cout << "No result to save!" << endl;
}

void Com_Load(CTabulator* Tabulator)
{
	string FileName;
	cout << "Input file name/path (no file type required): ";
	cin >> FileName;
	FileName += ".txt";

	try
	{
		Tabulator->LoadResultFromFile(FileName);
		cout << "Loaded from " << "'" << FileName << "'" << endl;
		Tabulator->PrintTabulationResult();
	}

	catch (exception e)
	{
		cout << endl << e.what() << endl;
	}
}