#include "Event.h"

std::ostream& operator<<(std::ostream& out, const Event& ev) {
  out << ev.mName << ' ' << ev.mDate;
  return out;
}