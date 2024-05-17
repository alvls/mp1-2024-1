#include "Receipt.h"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const Receipt& receipt) {
  os << std::left << std::setw(50) << "Название"
    << std::left << std::setw(20) << "Цена(руб./шт.)"
    << std::left << std::setw(20) << "Количество(шт.)"
    << std::left << std::setw(20) << "Общая стоимость(руб.)\n";

  for (auto& r : receipt.m_Items) {
    const Item& item = r.first;

    os << std::left << std::setw(50) << item.GetName()
      << std::left << std::setw(20) << item.GetPrice()
      << std::left << std::setw(20) << r.second
      << std::left << std::setw(20) << item.GetPrice() * r.second
      << "\n";
  }

  os << "------------------\n";
  os << "Скидка: " << receipt.GetTotalDiscount() << "руб. \n";
  os << "Сумма к оплате: " << receipt.GetTotalPrice() << "руб. \n";

  return os;
}