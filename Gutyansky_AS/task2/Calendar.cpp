#include "Calendar.h"

const Date* Calendar::GetDateByName(const std::string& name) const {
  for (size_t i = 0; i < mEventCount; i++) {
    if (mEvents[i].Name() == name) {
      return &mEvents[i].Date();
    }
  }

  return nullptr;
}

bool Calendar::TryAddEvent(const std::string& name, unsigned int day, unsigned int month, unsigned int year) {
  if (mEventCount >= EVENT_CAPACITY) {
    return false;
  }

  Date date(day, month, year);
  if (!date.IsValid()) {
    return false;
  }

  for (size_t i = 0; i < mEventCount; i++) {
    if (mEvents[i].Date() == date || mEvents[i].Name() == name) {
      return false;
    }
  }

  mEvents[mEventCount++] = Event(name, date);
  return true;
}