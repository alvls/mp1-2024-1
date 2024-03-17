#include <iostream>
#include <cmath>
#include "TemperatureConverter.h"

int main()
{
    CTemperatureConverter TempConv = 0.f;
    
    bool Running = true;

    while (Running)
    {
        std::string UserInput;
        std::cout << std::endl << "Input Temperature: ";
        std::cin >> UserInput;

        bool IsNumber = true;
        for (int i = 0; i < UserInput.length(); i++)
            if ( !( std::isdigit( UserInput.c_str()[i] ) || UserInput.c_str()[i] == '.' || UserInput.c_str()[i] == '-'))
            {
                IsNumber = false;
                break;
            }

        if (IsNumber)
        {
            double InputTemperature = std::stod(UserInput);

            TempConv.SetTemperature(InputTemperature);
            TempConv.PrintCurrentTemperature();
        }

        else
            std::cout << "Temperature value is incorrect";

        std::cout << std::endl << "Contiune? (0, 1): ";
        std::cin >> Running;
        std::cin.clear();
    }

    return 0;
}