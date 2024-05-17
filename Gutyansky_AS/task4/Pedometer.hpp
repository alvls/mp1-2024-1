#pragma once
#include <vector>
#include <fstream>
#include <stdexcept>
#include "StepsRecord.hpp"
#include "DateUtils.hpp"

class Pedometer {
private:
  int mDay = 0;
  int mMonth = 0;
  int mYear = 0;
  std::vector<StepsRecord> mRecords;
public:
  struct MaxStepsResponse {
    int Day, Month, Year;
    int Steps;

    MaxStepsResponse() : Day(0), Month(0), Year(0), Steps(0) {}
    MaxStepsResponse(int day, int month, int year, int steps) : Day(day), Month(month), Year(year), Steps(steps) {}

    bool Valid() const {
      return Steps > 0;
    }
  };

  struct DateResponse {
    int Day, Month, Year;

    DateResponse(int day, int month, int year) : Day(day), Month(month), Year(year) {}
  };

  void SetStartDate(int day, int month, int year) {
    if (!TestDate(day, month, year)) {
      throw std::runtime_error("Incorrect date was provided");
    }
    mDay = day;
    mMonth = month;
    mYear = year;
  }

  DateResponse GetStartDate() const {
    return { mDay, mMonth, mYear };
  }

  void AddRecord(StepsRecord record) {
    mRecords.push_back(record);
  }

  void AddRecord(int day, int month, int year, int startHour, int startMinute, int endHour, int endMinute, int steps) {
    AddRecord({ day, month, year, startHour, startMinute, endHour, endMinute, steps });
  }

  const StepsRecord &GetRecord(int index) const {
    return mRecords[index];
  }

  float GetAverageStepCount() const;

  float GetAverageStepCountMonth(int month, int year) const;

  float GetAverageWeekdaySteps(int weekday) const;

  MaxStepsResponse GetMaximumSteps() const;

  MaxStepsResponse GetMaximumSteps(int month, int year) const;
  void SaveFile(const std::string& path);

  void LoadFile(const std::string& path);
};