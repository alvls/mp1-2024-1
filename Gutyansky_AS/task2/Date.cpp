#include "Date.h"

bool Date::operator<(const Date& other) const {
  if (mYear < other.mYear) return true;
  if (mYear == other.mYear && mMonth < other.mMonth) return true;
  if (mYear == other.mYear && mMonth == other.mMonth && mDay < other.mDay) return true;

  return false;
}

bool Date::operator<=(const Date& other) const {
  return operator==(other) || operator<(other);
}

bool Date::operator>(const Date& other) const {
  if (mYear > other.mYear) return true;
  if (mYear == other.mYear && mMonth > other.mMonth) return true;
  if (mYear == other.mYear && mMonth == other.mMonth && mDay > other.mDay) return true;

  return false;
}

bool Date::operator>=(const Date& other) const {
  return operator==(other) || operator>(other);
}

std::ostream& operator<<(std::ostream& out, const Date& date) {
  out << date.mDay << '/' << date.mMonth << '/' << date.mYear;
  return out;
}