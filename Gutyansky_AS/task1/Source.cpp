#include <iostream>
#include "TemperatureConverter.h"


int main() {
  // changing console encoding to utf-8
  std::locale::global(std::locale("en_US.UTF8"));
  std::wcout.imbue(std::locale());

  TemperatureConverter converter;
  std::wcout << L"Default constructor:\n";
  converter.PrintAll(std::wcout);

  converter = TemperatureConverter(10);
  std::wcout << L"Parameterized constructor(10):\n";
  converter.PrintAll(std::wcout);

  std::wcout << L"Please enter new temperature(°C): \n";
  double val;
  std::wcin >> val;
  converter.SetCelsius(val);
  std::wcout << L"Updated temperature(" << val << L"):\n";
  converter.PrintAll(std::wcout);

  std::wcout << L"Printing in certain units of measurement:\n";
  converter.Print(std::wcout, TemperatureUnit::FAHRENHEIT);
  std::wcout << std::endl;
  converter.Print(std::wcout, TemperatureUnit::DELISLE);
  std::wcout << std::endl;
  converter.Print(std::wcout, TemperatureUnit::NEWTON);
  std::wcout << std::endl;

  return 0;
}