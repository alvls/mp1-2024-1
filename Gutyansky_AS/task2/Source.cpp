#include <iostream>
#include "Calendar.h"


int main() {
  Calendar calendar;

  calendar.TryAddEvent("Weekend", 25, 02, 2024);
  calendar.TryAddEvent("Birthday", 21, 04, 2005);

  if (!calendar.TryAddEvent("Abababa", 29, 02, 2025)) {
    std::cout << "Can't add event\n";
  }
  else {
    std::cout << "Event was added\n";
  }

  std::cout << "Birthday was at: " << *calendar.GetDateByName("Birthday") << std::endl;

  calendar.TryAddEvent("Test1", 31, 01, 2024);
  calendar.TryAddEvent("Test2", 31, 01, 2023);
  calendar.TryAddEvent("Test3", 31, 01, 2024);
  calendar.TryMoveForward("Test1", 0, 1, 0);
  calendar.TryMoveForward("Test2", 0, 1, 0);
  calendar.TryMoveForward("Test3", 0, 2, 0);
  std::cout << calendar;
  calendar.TryMoveBackward("Test2", 3, 0, 0);
  std::cout << calendar;

  TimeDelta delta;
  if (calendar.TryGetTimeDelta("Test2", 27, 02, 2023, delta)) {
    std::cout << delta.GetDays() << " days " << delta.GetMonths() << " months " << delta.GetYears() << " years\n";
  }
  if (calendar.TryGetTimeDelta("Birthday", 1, 3, 2024, delta)) {
    std::cout << delta.GetDays() << " days " << delta.GetMonths() << " months " << delta.GetYears() << " years\n";
  }
  if (calendar.TryGetTimeDelta("Abababa", 27, 02, 2023, delta)) {
    // won't be called because event abababa doen't exist
    std::cout << delta.GetDays() << " days " << delta.GetMonths() << " months " << delta.GetYears() << " years\n";
  }

  return 0;
}