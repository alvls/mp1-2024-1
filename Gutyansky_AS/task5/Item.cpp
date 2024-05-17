#include "Item.h"

std::ostream& operator<<(std::ostream& os, const Item& item) {
  os << "Штрихкод: " << item.GetBarcode().AsString() << "\n"
    << "Название: " << item.GetName() << '\n'
    << "Цена: " << item.GetPrice() << "руб \n"
    << "Скидка: " << item.GetDiscount() << "%\n";

  return os;
}