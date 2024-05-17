#include "Pedometer.hpp"

float Pedometer::GetAverageStepCount() const {
  if (mRecords.size() == 0) {
    return 0;
  }

  int sum = 0;
  for (const auto& rec : mRecords) {
    sum += rec.GetSteps();
  }

  return static_cast<float>(sum) / mRecords.size();
}

float Pedometer::GetAverageStepCountMonth(int month, int year) const {
  int sum = 0;
  int count = 0;
  for (const auto& rec : mRecords) {
    if (rec.GetMonth() == month && rec.GetYear() == year) {
      sum += rec.GetSteps();
      count++;
    }
  }

  if (count == 0) {
    return 0;
  }

  return static_cast<float>(sum) / count;
}

float Pedometer::GetAverageWeekdaySteps(int weekday) const {
  int sum = 0;
  int count = 0;
  for (const auto& rec : mRecords) {
    if (GetWeekday(rec.GetDay(), rec.GetMonth(), rec.GetYear()) == weekday) {
      sum += rec.GetSteps();
      count++;
    }
  }

  if (count == 0) {
    return 0;
  }

  return static_cast<float>(sum) / count;
}

Pedometer::MaxStepsResponse Pedometer::GetMaximumSteps() const {
  const StepsRecord* maxVal = nullptr;
  for (const auto& rec : mRecords) {
    if (maxVal == nullptr || rec.GetSteps() > maxVal->GetSteps()) {
      maxVal = &rec;
    }
  }

  if (maxVal == nullptr) {
    return MaxStepsResponse();
  }

  return { maxVal->GetDay(), maxVal->GetMonth(), maxVal->GetYear(), maxVal->GetSteps() };
}

Pedometer::MaxStepsResponse Pedometer::GetMaximumSteps(int month, int year) const {
  const StepsRecord* maxVal = nullptr;
  for (const auto& rec : mRecords) {
    if (month == rec.GetMonth() && year == rec.GetYear() &&
      (maxVal == nullptr || rec.GetSteps() > maxVal->GetSteps())) {
      maxVal = &rec;
    }
  }

  if (maxVal == nullptr) {
    return MaxStepsResponse();
  }

  return { maxVal->GetDay(), maxVal->GetMonth(), maxVal->GetYear(), maxVal->GetSteps() };
}

void Pedometer::SaveFile(const std::string& path) {
  std::ofstream fos(path);
  fos << mDay << ' ' << mMonth << ' ' << mYear << '\n';
  fos << mRecords.size() << '\n';
  for (const auto& rec : mRecords) {
    fos << rec.GetDay() << ' ' << rec.GetMonth() << ' ' << rec.GetYear() << ' '
      << rec.GetStartHour() << ' ' << rec.GetStartMinute() << ' ' << rec.GetEndHour() << ' '
      << rec.GetEndMinute() << ' ' << rec.GetSteps() << '\n';
  }
}

void Pedometer::LoadFile(const std::string& path) {
  std::ifstream fis(path);
  int day, month, year;
  fis >> day >> month >> year;
  size_t n;
  fis >> n;
  std::vector<StepsRecord> newRecords;
  for (int i = 0; i < n; i++) {
    int day, month, year, startHour, startMinute, endHour, endMinute, steps;
    fis >> day >> month >> year >> startHour >> startMinute >> endHour >> endMinute >> steps;
    newRecords.push_back({ day, month, year, startHour, startMinute, endHour, endMinute, steps });
  }

  mDay = day;
  mMonth = month;
  mYear = year;
  mRecords = newRecords;
}