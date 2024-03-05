#include "TimeDelta.h"

Date operator+(const Date& date, const TimeDelta& delta) {
  int day = date.GetDay();
  int month = date.GetMonth();
  int year = date.GetYear();

  year += delta.GetYears();

  month += delta.GetMonths();
  while (month > 12) {
    month -= 12;
    year++;
  }

  day += delta.GetDays();
  int numberOfDaysInMonth;
  while (day > (numberOfDaysInMonth = Date::NumberOfDaysInMonth(month, year))) {
    day -= numberOfDaysInMonth;
    month++;
    while (month > 12) {
      month -= 12;
      year++;
    }
  }

  Date newDate(day, month, year);
  return newDate;
}

Date operator-(const Date& date, const TimeDelta& delta) {
  int day = date.GetDay();
  int month = date.GetMonth();
  int year = date.GetYear();

  year -= delta.GetYears();
  month -= delta.GetMonths();
  while (month < 1) {
    month += 12;
    year--;
  }

  day -= delta.GetDays();
  while (day < 1) {
    month--;
    while (month < 1) {
      month += 12;
      year--;
    }
    day += Date::NumberOfDaysInMonth(month, year);
  }

  return Date(day, month, year);
}

TimeDelta operator-(const Date& left, const Date& right) {
  if (left == right) {
    return TimeDelta(0, 0, 0);
  }

  Date l, r;
  if (left < right) {
    l = left; r = right;
  }
  else {
    l = right; r = left;
  }

  const TimeDelta yearDelta(0, 0, 1);
  const TimeDelta monthDelta(0, 1, 0);
  const TimeDelta dayDelta(1, 0, 0);

  Date temp;
  int years = 0;
  while ((temp = l + yearDelta) <= r) {
    l = temp;
    years++;
  }

  int months = 0;
  while ((temp = l + monthDelta) <= r) {
    l = temp;
    months++;
  }

  int days = 0;
  while ((temp = l + dayDelta) <= r) {
    l = temp;
    days++;
  }

  return TimeDelta(days, months, years);
}