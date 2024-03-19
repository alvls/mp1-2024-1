#pragma once
#include <iostream>
#include <stdexcept>
#include "DateUtils.hpp"

class StepsRecord {
private:
  int mDay;
  int mMonth;
  int mYear;
  int mStartHour;
  int mStartMinute;
  int mEndHour;
  int mEndMinute;
  int mSteps;

  bool testTimes() const {
    if (mStartHour < 0 || mStartHour > 23 ||
      mEndHour < 0 || mEndHour > 23 ||
      mStartMinute < 0 || mStartMinute > 59 ||
      mEndMinute < 0 || mEndMinute > 59) {
      return false;
    }

    return !(mStartHour > mEndHour ||
      mStartHour == mEndHour && mStartMinute > mEndMinute);
  }
public:
  StepsRecord(int day, int month, int year,
    int startHour, int startMinute,
    int endHour, int endMinute, int steps) :
    mDay(day), mMonth(month), mYear(year),
    mStartHour(startHour), mStartMinute(startMinute),
    mEndHour(endHour), mEndMinute(endMinute), mSteps(steps) {
    
    if (!TestDate(mDay, mMonth, mYear)) {
      throw std::runtime_error("Incorrect date was provided");
    }

    if (!testTimes()) {
      throw std::runtime_error("Incorrect start/end time was provided");
    }

    if (mSteps <= 0) {
      throw std::runtime_error("Step count must be greater than zero");
    }
  }

  int GetDay() const {
    return mDay;
  }

  int GetMonth() const {
    return mMonth;
  }

  int GetYear() const {
    return mYear;
  }

  int GetStartHour() const {
    return mStartHour;
  }

  int GetStartMinute() const {
    return mStartMinute;
  }

  int GetEndHour() const {
    return mEndHour;
  }

  int GetEndMinute() const {
    return mEndMinute;
  }

  int GetSteps() const {
    return mSteps;
  }
};

std::ostream& operator<<(std::ostream& out, const StepsRecord& record);