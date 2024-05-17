#pragma once
#include <vector>
#include <stdexcept>
#include "Barcode.h"
#include "Item.h"

class Warehouse {
private:
  std::vector<Item> m_Items;

public:
  void RegisterItem(const Item& item) {
    if (HasItem(item.GetBarcode())) {
      throw std::runtime_error("Barcode " + item.GetBarcode().AsString() + " already used");
    }

    m_Items.push_back(item);
  }

  bool HasItem(const Barcode& barcode) const {
    for (const Item& item : m_Items) {
      if (item.GetBarcode() == barcode) {
        return true;
      }
    }

    return false;
  }

  const Item& GetItem(const Barcode& barcode) const {
    for (const Item& item : m_Items) {
      if (item.GetBarcode() == barcode) {
        return item;
      }
    }

    throw std::runtime_error("Barcode " + barcode.AsString() + " not found");
  }
};
