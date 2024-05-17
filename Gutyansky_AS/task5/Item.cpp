#include "Item.h"

std::ostream& operator<<(std::ostream& os, const Item& item) {
  os << "��������: " << item.GetBarcode().AsString() << "\n"
    << "��������: " << item.GetName() << '\n'
    << "����: " << item.GetPrice() << "��� \n"
    << "������: " << item.GetDiscount() << "%\n";

  return os;
}