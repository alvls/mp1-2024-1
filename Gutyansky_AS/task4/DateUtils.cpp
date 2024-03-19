#include "DateUtils.hpp"
#include <ctime>
#include <iostream>

bool TestDate(int day, int month, int year) {
  tm test_time;
  test_time.tm_mday = day;
  test_time.tm_mon = month - 1;
  test_time.tm_year = year - 1900;
  mktime(&test_time);
  return test_time.tm_mday == day && test_time.tm_mon == month - 1 && test_time.tm_year == year - 1900;
}

int GetWeekday(int day, int month, int year) {
  static int t[] = { 0, 3, 2, 5, 0, 3,
                     5, 1, 4, 6, 2, 4 };
  year -= month < 3;
  return (year + year / 4 - year / 100 +
    year / 400 + t[month - 1] + day) % 7;
}