#pragma once
#include <iostream>

class Date {
private:
  int mDay;
  int mMonth;
  int mYear;
public:
  Date() : mDay(1), mMonth(1), mYear(1) {}
  Date(int day, int month, int year) :
    mDay(day), mMonth(month), mYear(year) {}

  int GetDay() const {
    return mDay;
  }

  int GetMonth() const {
    return mMonth;
  }

  int GetYear() const {
    return mYear;
  }

  bool operator<(const Date& other) const;
  bool operator<=(const Date& other) const;
  bool operator>(const Date& other) const;
  bool operator>=(const Date& other) const;

  bool operator!=(const Date& other) const {
    return mDay != other.mDay || mMonth != other.mMonth || mYear != other.mYear;
  }

  bool operator==(const Date& other) const {
    return mDay == other.mDay && mMonth == other.mMonth && mYear == other.mYear;
  }
  

  friend std::ostream& operator<<(std::ostream& out, const Date& date);

  bool IsValid() const {
    return mDay >= 1 && mMonth >= 1 && mYear >= 1 &&
      mDay <= NumberOfDaysInMonth(mMonth, mYear) && mMonth <= 12 && mYear <= 2100;
  }

  static bool IsLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
  }

  static int NumberOfDaysInMonth(int month, int year) {
    if (month == 2) {
      if (IsLeapYear(year)) {
        return 29;
      }
      else {
        return 28;
      }
    }
    else if (month % 2 == 0) {
      return 30;
    }
    else {
      return 31;
    }
  }
};