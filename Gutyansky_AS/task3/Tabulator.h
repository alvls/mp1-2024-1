#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "Point.h"

typedef float (*FunctionPtr)(float);

class Tabulator {
private:
  FunctionPtr mFunction;
  float mLowerBound;
  float mUpperBound;
  int mPointsAmount;
public:
  Tabulator(FunctionPtr f, float lowerBound = 0.0f, float upperBound = 10.0f, int pointsAmount = 10) {
    SetFunction(f);
    SetBounds(lowerBound, upperBound);
    SetPointsAmount(pointsAmount);
  }

  void SetFunction(FunctionPtr f) {
    if (f == nullptr) {
      throw std::invalid_argument("f was nullptr.");
    }

    mFunction = f;
  }

  FunctionPtr GetFunction() const {
    return mFunction;
  }

  void SetBounds(float lowerBound, float upperBound) {
    if (lowerBound > upperBound) {
      throw std::runtime_error("Lower bound of tabulation must be less or equal to upper bound.");
    }

    mLowerBound = lowerBound;
    mUpperBound = upperBound;
  }

  float GetLowerBound() const {
    return mLowerBound;
  }

  float GetUpperBound() const {
    return mUpperBound;
  }

  float GetSegmentLength() const {
    return mUpperBound - mLowerBound;
  }

  float GetTabulationStep() const {
    return GetSegmentLength() / (mPointsAmount - 1);
  }

  void SetPointsAmount(int amount) {
    if (amount < 2) {
      throw std::invalid_argument("Points amount must be 2 or greater.");
    }

    mPointsAmount = amount;
  }

  int GetPointsAmount() const {
    return mPointsAmount;
  }

  Point GetTabulationPoint(int pointIndex) const;
  std::vector<Point> GetTabulationResult() const;
};

std::ostream& operator<<(std::ostream& out, const Tabulator& tabulator);
