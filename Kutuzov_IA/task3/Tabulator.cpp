#include "Tabulator.h"
#include <cmath>
#include <iostream>

#define NUM_FUNCTIONS 4


// Constructor / Destructor
CTabulator::CTabulator(int In_FuncID = 0, int In_NumPoints = 3, double In_Min = 0.0, double In_Max = 1.0)
{
    FuncID = In_FuncID;
    NumPoints = In_NumPoints;
    Min = In_Min;
    Max = In_Max;

}

CTabulator::~CTabulator() {}

// Selects current function by its ID
void CTabulator::SetFunction(int In_FuncID) { FuncID = In_FuncID; bHasTabulated = false; }

// Returns pointer to the current function
Function CTabulator::GetFunction_ptr()
{
    Function AvailableFunctions[NUM_FUNCTIONS] = {&std::sin, &std::cos, &std::log, &std::abs};

    if (FuncID < NUM_FUNCTIONS)
        return AvailableFunctions[FuncID];

    else
    {
        std::cout << std::endl << "Invalid Functin ID, using default function std::sin" << std::endl;
        return AvailableFunctions[0];
    }
}

// Set / Get number of tabulation points
void CTabulator::SetNumPoints(int In_NumPoints) { NumPoints = In_NumPoints; bHasTabulated = false;}

int CTabulator::GetNumPoints() { return NumPoints; }

// Set / Get range of tabulation
void CTabulator::SetRange(double In_Min, double In_Max)
{
    Min = In_Min;
    Max = In_Max;

    bHasTabulated = false;
}

double CTabulator::GetRangeMin() { return Min; }
double CTabulator::GetRangeMax() { return Max; }

// Returns x value in a certain point (based on range and num points)
double CTabulator::GetPointValue(int Point)
{
    double Step = (Max - Min) / (NumPoints - 1);
    return Min + Point * Step;
}

// Tabulation itself
void CTabulator::Tabulate()
{
    TabulatedPoints.empty();

    for (int p = 0; p < NumPoints; p++)
        TabulatedPoints.push_back(GetFunction_ptr()(GetPointValue(p)));

    bHasTabulated = true;
}

// Printing and saving result
bool CTabulator::HasTabulated() { return HasTabulated; }
bool CTabulator::PrintResultTabulate()
{
    
}

bool CTabulator::SaveResultToFile(std::string Path)
{

}