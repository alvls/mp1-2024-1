#pragma once
#include <unordered_map>
#include <stdexcept>
#include "Barcode.h"
#include "Item.h"

class Warehouse {
private:
  std::unordered_map<Barcode, Item> m_Items;

public:
  void RegisterItem(const Barcode& barcode, const Item& item) {
    if (m_Items.find(barcode) != m_Items.end()) {
      throw std::runtime_error("Barcode " + barcode.AsString() + " already used");
    }

    m_Items[barcode] = item;
  }

  bool TryGetItem(const Barcode& barcode, Item& item) const {
    if (m_Items.find(barcode) != m_Items.end()) {
      item = m_Items[barcode];
      return true;
    }

    return false;
  }
};
