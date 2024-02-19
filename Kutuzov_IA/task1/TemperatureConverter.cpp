#include "TemperatureConverter.h"
#include <iostream>


// Constructor
CTemperatureConverter::CTemperatureConverter(double InTemp, TemperatureFormat Format)
{
    CelsiusTemp = ConvertTemperature(InTemp, Format);
}

// Methods
// Converts temperature from in format to out format
double CTemperatureConverter::ConvertTemperature(double InTemp, TemperatureFormat InFormat, TemperatureFormat OutFormat)
{
    if (InFormat == C) 
        switch (OutFormat)
        {
        case C: return InTemp;
        case F: return InTemp * 1.8f + 32.f;
        case K: return InTemp + 273.15f;
        case R: return (InTemp + 273.15f) * 1.8f;
        }

    else
        switch (InFormat)
        {
        case F: return ConvertTemperature((InTemp - 32.f) * 5.f / 9.f, C, OutFormat);
        case K: return ConvertTemperature(InTemp - 273.15f, C, OutFormat);
        case R: return ConvertTemperature(InTemp / 1.8f - 273.15f, C, OutFormat);
        }

    return 0.f;
}

// Returns current temperature in the given format
double CTemperatureConverter::GetTemperature(TemperatureFormat Format)
{
    return ConvertTemperature(CelsiusTemp, C, Format);
}

// Sets temperature in the given format
void CTemperatureConverter::SetTemperature(double InTemp, TemperatureFormat Format)
{
    CelsiusTemp = ConvertTemperature(InTemp, Format);
}