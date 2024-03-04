#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cmath>

typedef float (*FunctionPtr)(float);

struct Point {
  float x;
  float y;
};

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
    if (lowerBound >= upperBound) {
      throw std::runtime_error("Lower bound of tabulation must be less than upper bound.");
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

  float GetSegmentSize() const {
    return mUpperBound - mLowerBound;
  }

  float GetTabulationStep() const {
    return GetSegmentSize() / (mPointsAmount - 1);
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

  Point GetTabulationPoint(int pointIndex) const {
    if (pointIndex >= mPointsAmount) {
      throw std::out_of_range("Index was out of range.");
    }

    float argument = mLowerBound + pointIndex * GetTabulationStep();
    float result = mFunction(argument);

    return { argument, result };
  }

  std::vector<Point> GetTabulationResult() const {
    std::vector<Point> points(mPointsAmount);
    for (int i = 0; i < mPointsAmount; i++) {
      points[i] = GetTabulationPoint(i);
    }

    return points;
  }
};

std::ostream& operator<<(std::ostream& out, const Tabulator& tabulator) {
  out << std::setw(6) << std::left << "N";
  out << std::setw(20) << std::left << "Argument";
  out << std::setw(20) << std::left << "Value" << std::endl;
  
  for (size_t i = 0; i < tabulator.GetPointsAmount(); i++) {
    Point p = tabulator.GetTabulationPoint(i);
    out << std::setw(6) << std::left << i + 1;
    out << std::setw(20) << std::left << p.x;
    out << std::setw(20) << std::left << p.y << std::endl;
  }

  return out;
}

class TabulatorSaver {
private:
  std::string mPath;
public:
  TabulatorSaver(const std::string& path) : mPath(path) { }

  void Save(const Tabulator& tabulator) {
    std::ofstream out(mPath);
    out << tabulator;
    out.close();
  }
};

float f(float x) {
  return x * x;
}

int main() {
  Tabulator t(f);
  t.SetBounds(0, 10);
  t.SetPointsAmount(100);

  TabulatorSaver saver("test.txt");
  saver.Save(t);

  std::cout << t;
  return 0;
}