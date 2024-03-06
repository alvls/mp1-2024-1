#include <iostream>
#include <cmath>
#include "Tabulator.h"
#include "TabulatorFileSaver.h"

float f(float x) {
  return sin(cos(x)) + tan(x)*x*x;
}

int main() {
  Tabulator t(f);
  t.SetBounds(0, 1);
  t.SetPointsAmount(10);

  TabulatorFileSaver saver("test.txt");
  saver.Save(t);

  std::cout << "Tabulating from " << t.GetLowerBound() << " to " << t.GetUpperBound()
    << "\nSegment length: " << t.GetSegmentLength() << "\nTabulation step: " << t.GetTabulationStep() << std::endl;
  std::cout << t;
  return 0;
}