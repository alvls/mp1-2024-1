#pragma once
#include <iostream>
#include "Event.h"
#include "TimeDelta.h"

class Calendar {
private:
  const size_t EVENT_CAPACITY = 30;

  Event* mEvents;
  size_t mEventCount;

  Event* GetEventByName(const std::string& name) const;
  Event* GetEventByDate(const Date& date) const;
public:
  Calendar() {
    mEvents = new Event[EVENT_CAPACITY];
    mEventCount = 0;
  }

  ~Calendar() {
    delete[] mEvents;
  }

  size_t GetLength() const {
    return mEventCount;
  }

  bool TryAddEvent(const std::string& name, int day, int month, int year);
  bool TryMoveForward(const std::string& name, int days, int months, int years);
  bool TryMoveBackward(const std::string& name, int days, int months, int years);
  bool TryGetTimeDelta(const std::string& name, int fromDay, int fromMonth, int fromYear, TimeDelta& delta);
  const Date* GetDateByName(const std::string& name) const;
  
  friend std::ostream& operator<<(std::ostream& out, const Calendar& calendar);
};

