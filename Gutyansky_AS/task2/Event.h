#pragma once
#include <string>
#include "Date.h"

class Event {
private:
  std::string mName;
  Date mDate;
public:
  Event() = default;
  Event(const std::string& name, const Date& date) :
    mName(name), mDate(date) {}

  const Date& Date() const {
    return mDate;
  }

  const std::string& Name() const {
    return mName;
  }

  friend std::ostream& operator<<(std::ostream& out, const Event& ev);
};