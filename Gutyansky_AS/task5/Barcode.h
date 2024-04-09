#pragma once
#include <string>
#include <stdexcept>
#include <cctype>

const unsigned int BARCODE_LENGTH = 4;

class Barcode {
private:
  char m_Data[BARCODE_LENGTH];
public:
  Barcode(const std::string& str) {
    if (str.size() != BARCODE_LENGTH) {
      throw std::runtime_error("Barcode string must have length " + std::to_string(BARCODE_LENGTH));
    }

    for (size_t i = 0; i < BARCODE_LENGTH; i++) {
      if (!isdigit(str[i])) {
        throw std::runtime_error("Barcode string must contain only digits");
      }
      m_Data[i] = str[i];
    }
  }

  std::string AsString() const {
    return std::string(m_Data, BARCODE_LENGTH);
  }

  bool operator==(const Barcode& barcode) const {
    for (size_t i = 0; i < BARCODE_LENGTH; i++) {
      if (m_Data[i] != barcode.m_Data[i]) {
        return false;
      }
    }

    return true;
  }
};