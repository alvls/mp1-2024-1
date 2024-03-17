#include "Tabulator.h"
#include <iostream>
#include <fstream>




// Constructor / Destructor
CTabulator::CTabulator(int In_FuncID, int In_NumPoints, double In_Min, double In_Max)
{
    FuncID = In_FuncID;
    NumPoints = In_NumPoints;
    Min = In_Min;
    Max = In_Max;

}

CTabulator::~CTabulator() 
{
    // idk, but its in the task, so...
}


// Same signature as the constructor, allows to reinitialise the class
void CTabulator::ReInit(int In_FuncID, int In_NumPoints, double In_Min, double In_Max)
{
    bHasTabulated = false;
    TabulatedPoints.clear();

    FuncID = In_FuncID;
    NumPoints = In_NumPoints;
    Min = In_Min;
    Max = In_Max;
}


// Selects current function by its ID
void CTabulator::SetFunction(int In_FuncID) { FuncID = In_FuncID; bHasTabulated = false; }

// Returns pointer to the current function
Function CTabulator::GetFunction_ptr()
{
    if (FuncID < NUM_FUNCTIONS)
        return AvailableFunctions[FuncID];

    else
        throw(std::exception("Invalid function ID"));
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
    TabulatedPoints.clear();

    for (int p = 0; p < NumPoints; p++)
        TabulatedPoints.push_back(GetFunction_ptr()(GetPointValue(p)));

    bHasTabulated = true;
}


// Printing and saving result
bool CTabulator::HasTabulated() { return bHasTabulated; }
bool CTabulator::PrintTabulationResult()
{
    if (HasTabulated())
    {
        std::cout << std::endl << "Function ID: " << FuncID << "; Range: " << Min << " - " << Max << "; Number of points: " << NumPoints << std::endl;

        for (size_t i = 0; i < TabulatedPoints.size(); i++)
        {
            std::cout << i + 1 << " : x = " << GetPointValue(i) << " : f(x) = " << TabulatedPoints[i] << std::endl;
        }
    }

    return HasTabulated();
}

bool CTabulator::SaveResultToFile(std::string Path)
{
    std::ofstream file(Path);

    if (HasTabulated())
    {
        file << FuncID << std::endl << Min << std::endl << Max << std::endl << NumPoints << std::endl;

        for (size_t i = 0; i < TabulatedPoints.size(); i++)
        {
            file << TabulatedPoints[i] << std::endl;
        }
    }

    file.close();

    return HasTabulated();
}


// Loading from file
void CTabulator::LoadResultFromFile(std::string Path)
{
    std::ifstream file(Path);

    if (!file.is_open())
    {
        file.close();
        throw(std::exception("No such file!"));
    }

    int InFuncID;
    int InNumPoints;
    double InMin, InMax;

    file >> InFuncID >> InMin >> InMax >> InNumPoints;
    ReInit(InFuncID, InNumPoints, InMin, InMax);

    for (int i = 0; i < InNumPoints; i++)
    {
        double PointValue;
        file >> PointValue;
        TabulatedPoints.push_back(PointValue);
    }

    file.close();

    bHasTabulated = true;
}