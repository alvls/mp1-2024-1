#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include "TemperatureUnit.h"


class TemperatureConverter {
private:
  double mCelsius;

public:
  TemperatureConverter() : mCelsius(0.0) {}
  TemperatureConverter(double initialValue) : mCelsius(initialValue) {}

  void SetCelsius(double newValue) {
    mCelsius = newValue;
  }

  double Celsius() const {
    return mCelsius;
  }

  double Fahrenheit() const {
    return (mCelsius * 1.8) + 32;
  }

  double Calvin() const {
    return mCelsius + 273.15;
  }

  double Rankine() const {
    return Calvin() * 1.8;
  }

  double Romer() const {
    return (mCelsius / 1.9047619) + 7.5;
  }

  double Newton() const {
    return mCelsius / 3.03030303;
  }

  double Delisle() const {
    return (100 - mCelsius) * 1.5;
  }

  double Reaumur() const {
    return mCelsius / 1.25;
  }

  double Temperature(TemperatureUnit unit) const {
    switch (unit)
    {
    case TemperatureUnit::CELSIUS:
      return Celsius();
    case TemperatureUnit::FAHRENHEIT:
      return Fahrenheit();
    case TemperatureUnit::CALVIN:
      return Calvin();
    case TemperatureUnit::RANKINE:
      return Rankine();
    case TemperatureUnit::ROMER:
      return Romer();
    case TemperatureUnit::NEWTON:
      return Newton();
    case TemperatureUnit::DELISLE:
      return Delisle();
    case TemperatureUnit::REAUMUR:
      return Reaumur();
    default:
      assert(0 && "Invalid temperature unit!");
    }
  }

  void PrintAll(std::wostream& out, const std::wstring& divider = L"\n", const std::wstring& end = L"\n") const {
    out << Celsius() << L"°C" << divider << Fahrenheit() << L"°F" << divider <<
      Calvin() << L"K" << divider << Rankine() << L"°Ra" << divider << Romer() << L"°Ro" <<
      divider << Newton() << L"°N" << divider << Delisle() << L"°De" << divider << Reaumur() << L"°Re" << end;
  }

  void Print(std::wostream& out, TemperatureUnit unit = TemperatureUnit::CELSIUS) const {
    switch (unit)
    {
    case TemperatureUnit::CELSIUS:
      out << Celsius() << L"°C";
      break;
    case TemperatureUnit::FAHRENHEIT:
      out << Fahrenheit() << L"°F";
      break;
    case TemperatureUnit::CALVIN:
      out << Calvin() << L"K";
      break;
    case TemperatureUnit::RANKINE:
      out << Rankine() << L"°Ra";
      break;
    case TemperatureUnit::ROMER:
      out << Romer() << L"°Ro";
      break;
    case TemperatureUnit::NEWTON:
      out << Newton() << L"°N";
      break;
    case TemperatureUnit::DELISLE:
      out << Delisle() << L"°De";
      break;
    case TemperatureUnit::REAUMUR:
      out << Reaumur() << L"°Re";
      break;
    default:
      assert(0 && "Invalid temperature unit!");
    }
  }
};