#include <iostream>
#include <cmath>
#include "TemperatureConverter.h"

int main()
{
    CTemperatureConverter TempConv = 0.f;
    
    bool Running = true;

    while (Running)
    {
        double UserInput;
        std::cout << "Input Temperature: ";
        std::cin >> UserInput;

        if (-1000.f <= UserInput &&  UserInput <= 1000.f)
        {
            TempConv.SetTemperature(UserInput);
            std::cout << TempConv.GetTemperature() << "   " << TempConv.GetTemperature(F) << "   " << TempConv.GetTemperature(K) << "   " << TempConv.GetTemperature(R);
        }

        Running = false;
    }

    return 0;
}