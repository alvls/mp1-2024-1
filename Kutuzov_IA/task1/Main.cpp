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
        std::cout << std::endl << "Input Temperature: ";
        std::cin >> UserInput;
        std::cin.clear();

        if (-1000.f <= UserInput &&  UserInput <= 1000.f)
        {
            TempConv.SetTemperature(UserInput);
            TempConv.PrintCurrentTemperature();
        }

        std::cout << std::endl << "Contiune? (0, 1): ";
        std::cin >> Running;
    }

    return 0;
}