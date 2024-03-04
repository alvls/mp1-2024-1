#pragma once
#include <vector>
#include <string>

typedef double (*Function) (double);

class CTabulator
{
    int FuncID;
    int NumPoints;
    double Min, Max;

    bool bHasTabulated = false;
    std::vector<double> TabulatedPoints;

public:
    // Constructor / Destructor
    CTabulator(int In_FuncID = 0, int In_NumPoints = 3, double In_Min = 0.0, double In_Max = 1.0);
    ~CTabulator();

    // Selects current function by its ID
    void SetFunction(int In_FuncID);

    // Returns pointer to the current function
    Function GetFunction_ptr();

    // Set / Get number of tabulation points
    void SetNumPoints(int In_NumPoints);
    int GetNumPoints();

    // Set / Get range of tabulation
    void SetRange(double In_Min, double In_Max);
    double GetRangeMin();
    double GetRangeMax();

    // Returns x value in a certain point (based on range and num points)
    double GetPointValue(int Point);

    // Tabulation itself
    void Tabulate();

    // Printing and saving result
    bool HasTabulated();
    bool PrintResultTabulate();
    bool SaveResultToFile(std::string Path);
};