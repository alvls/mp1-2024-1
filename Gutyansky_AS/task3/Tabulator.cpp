#include "Tabulator.h"

Point Tabulator::GetTabulationPoint(int pointIndex) const {
  if (pointIndex >= mPointsAmount) {
    throw std::out_of_range("Index was out of range.");
  }

  float argument = mLowerBound + pointIndex * GetTabulationStep();
  float result = mFunction(argument);

  return { argument, result };
}

std::vector<Point> Tabulator::GetTabulationResult() const {
  std::vector<Point> points(mPointsAmount);
  for (int i = 0; i < mPointsAmount; i++) {
    points[i] = GetTabulationPoint(i);
  }

  return points;
}

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
