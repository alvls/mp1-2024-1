#pragma once
#include <iostream>
#include "Event.h"

class Calendar {
private:
  const size_t EVENT_CAPACITY = 30;

  Event* mEvents;
  size_t mEventCount;
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

  bool TryAddEvent(const std::string& name, unsigned int day, unsigned int month, unsigned int year);
  const Date* GetDateByName(const std::string& name) const;
  void Print(std::ostream& out) const;
};
