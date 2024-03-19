#pragma once
#include <string>
#include <fstream>
#include "Tabulator.h"

class TabulatorFileSaver {
private:
  std::string mPath;
public:
  TabulatorFileSaver(const std::string& path) : mPath(path) { }

  void Save(const Tabulator& tabulator) {
    std::ofstream out(mPath);
    out << tabulator;
    out.close();
  }
};