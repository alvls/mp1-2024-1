#pragma once

#include <string>

typedef enum {C, F, K, R} TemperatureFormat;

class CTemperatureConverter
{
    double CelsiusTemp;

public:
    // Constructor
    CTemperatureConverter(double InTemp = 0.f, TemperatureFormat Format = C);

    // Methods
    // Converts temperature from in format to out format
    double ConvertTemperature(double InTemp, TemperatureFormat InFormat, TemperatureFormat OutFormat = C);

    // Returns current temperature in the given format
    double GetTemperature(TemperatureFormat Format = C);

    // Sets temperature in the given format
    void SetTemperature(double InTemp, TemperatureFormat Format = C);

    // Returns the name of the requested format
    std::string GetFormatName(TemperatureFormat Format);

    // Outputs current temperature in all available formats to the console
    void PrintCurrentTemperature();
};