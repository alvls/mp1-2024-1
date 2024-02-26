#pragma once
#include <iosfwd>

class Date {
private:
  unsigned int mDay;
  unsigned int mMonth;
  unsigned int mYear;
public:
  Date() : mDay(1), mMonth(1), mYear(1) {}
  Date(unsigned int day, unsigned int month, unsigned int year) :
    mDay(day), mMonth(month), mYear(year) {}

  bool operator==(const Date& other) const {
    return mDay == other.mDay && mMonth == other.mMonth && mDay == other.mYear;
  }

  std::ostream& operator<<(std::ostream& out) const {
    out << mDay << '/' << mMonth << '/' << mYear;
    return out;
  }

  bool IsValid() const {
    return mDay >= 1 && mMonth >= 1 && mYear >= 1 &&
      mDay <= NumberOfDaysInMonth() && mMonth <= 12 && mYear <= 2100;
  }

  unsigned int NumberOfDaysInMonth() const {
    if (mMonth == 2) {
      if ((mYear % 4 == 0 && mYear % 100 != 0) || (mYear % 400 == 0)) {
        return 29;
      }
      else {
        return 28;
      }
    }
    else if (mMonth % 2 == 0) {
      return 30;
    }
    else {
      return 31;
    }
  }
};
