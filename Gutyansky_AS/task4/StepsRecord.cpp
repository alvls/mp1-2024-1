#include "StepsRecord.hpp"

std::ostream& operator<<(std::ostream& out, const StepsRecord& record) {
  out << "Date: " << record.GetDay() << '.' << record.GetMonth() << '.' << record.GetYear() << '\n';
  out << "Start time: " << record.GetStartHour() << ':' << record.GetStartMinute() << '\n';
  out << "End time: " << record.GetEndHour() << ':' << record.GetEndMinute() << '\n';
  out << "Steps: " << record.GetSteps() << '\n';

  return out;
}