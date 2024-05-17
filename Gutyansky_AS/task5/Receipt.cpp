#include "Receipt.h"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const Receipt& receipt) {
  os << std::left << std::setw(50) << "��������"
    << std::left << std::setw(20) << "����(���./��.)"
    << std::left << std::setw(20) << "����������(��.)"
    << std::left << std::setw(20) << "����� ���������(���.)\n";

  for (auto& r : receipt.m_Items) {
    const Item& item = r.first;

    os << std::left << std::setw(50) << item.GetName()
      << std::left << std::setw(20) << item.GetPrice()
      << std::left << std::setw(20) << r.second
      << std::left << std::setw(20) << item.GetPrice() * r.second
      << "\n";
  }

  os << "------------------\n";
  os << "������: " << receipt.GetTotalDiscount() << "���. \n";
  os << "����� � ������: " << receipt.GetTotalPrice() << "���. \n";

  return os;
}