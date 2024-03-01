#pragma once
#include "Date.h"

class TimeDelta {
private:
  int mYears;
  int mMonths;
  int mDays;
public:
  TimeDelta() : mDays(0), mMonths(0), mYears(0) {}
  TimeDelta(int days, int months, int years) : mDays(days), mMonths(months), mYears(years) {}

  int GetDays() const {
    return mDays;
  }

  int GetMonths() const {
    return mMonths;
  }

  int GetYears() const {
    return mYears;
  }

  bool IsValid() const {
    return 0 <= mDays && mDays <= 31 &&
      0 <= mMonths && mMonths <= 12 &&
      0 <= mYears && mYears <= 2100;
  }
};

Date operator+(const Date& date, const TimeDelta& delta);
Date operator-(const Date& date, const TimeDelta& delta);
TimeDelta operator-(const Date& left, const Date& right);