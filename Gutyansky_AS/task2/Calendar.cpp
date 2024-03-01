#include "Calendar.h"

Event* Calendar::GetEventByName(const std::string& name) const {
  for (size_t i = 0; i < mEventCount; i++) {
    if (mEvents[i].Name() == name) {
      return &mEvents[i];
    }
  }

  return nullptr;
}

Event* Calendar::GetEventByDate(const Date& date) const {
  for (size_t i = 0; i < mEventCount; i++) {
    if (mEvents[i].Date() == date) {
      return &mEvents[i];
    }
  }

  return nullptr;
}

const Date* Calendar::GetDateByName(const std::string& name) const {
  const Event* event = GetEventByName(name);
  if (event == nullptr) {
    return nullptr;
  }

  return &event->Date();
}

bool Calendar::TryAddEvent(const std::string& name, int day, int month, int year) {
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

bool Calendar::TryMoveForward(const std::string& eventName, int days, int months, int years) {
  TimeDelta delta(days, months, years);
  if (!delta.IsValid()) {
    return false;
  }

  Event* event = GetEventByName(eventName);
  if (event == nullptr) {
    return false;
  }

  Date newDate = event->Date() + delta;
  if (!newDate.IsValid()) {
    return false;
  }

  if (GetEventByDate(newDate) != nullptr) {
    return false;
  }

  *event = Event(event->Name(), newDate);

  return true;
}

bool Calendar::TryMoveBackward(const std::string& eventName, int days, int months, int years) {
  TimeDelta delta(days, months, years);
  if (!delta.IsValid()) {
    return false;
  }

  Event* event = GetEventByName(eventName);
  if (event == nullptr) {
    return false;
  }

  Date newDate = event->Date() - delta;
  if (!newDate.IsValid()) {
    return false;
  }

  if (GetEventByDate(newDate) != nullptr) {
    return false;
  }

  *event = Event(event->Name(), newDate);

  return true;
}

bool Calendar::TryGetTimeDelta(const std::string& name, int fromDay, int fromMonth, int fromYear, TimeDelta& delta) {
  Event* event = GetEventByName(name);
  if (event == nullptr) {
    return false;
  }

  Date fromDate = Date(fromDay, fromMonth, fromYear);
  if (!fromDate.IsValid()) {
    return false;
  }

  delta = event->Date() - fromDate;
  return true;
}

std::ostream& operator<<(std::ostream& out, const Calendar& calendar) {
  for (size_t i = 0; i < calendar.mEventCount; i++) {
    out << i + 1 << ". " << calendar.mEvents[i] << " " << std::endl;
  }
  return out;
}