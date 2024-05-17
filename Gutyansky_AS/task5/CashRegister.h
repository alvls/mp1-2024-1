#pragma once
#include <stdexcept>
#include <list>
#include "Warehouse.h"
#include "Item.h"
#include "Receipt.h"

class CashRegister {
private:
  Warehouse* m_Warehouse;
  std::list<std::pair<Item, int>> m_Products;

  const Item& GetItem(const Barcode& barcode) {    
    return m_Warehouse->GetItem(barcode);
  }
public:
  CashRegister(Warehouse* warehouse) : m_Warehouse(warehouse) {
    if (warehouse == nullptr) {
      throw std::runtime_error("No warehouse provided");
    }
  }

  void ScanItem(const Barcode& barcode) {
    const Item& item = GetItem(barcode);
    for (auto& p : m_Products) {
      if (p.first == item) {
        p.second++;
        return;
      }
    }

    m_Products.push_back(std::make_pair(item, 1));
  }

  const Item& GetItemInfo(const Barcode& barcode) const {
    return m_Warehouse->GetItem(barcode);
  }

  bool RemoveItem(const Barcode& barcode) {
    const Item& item = GetItem(barcode);
    for (auto& it = m_Products.begin(); it != m_Products.end(); it++) {
      if (it->first == item) {
        it->second--;

        if (it->second <= 0) {
          m_Products.erase(it);
          return true;
        }
      }
    }
    
    return false;
  }

  Receipt CreateReceipt() const {
    Receipt receipt;
    for (auto& r : m_Products) {
      receipt.AddItems(r.first, r.second);
    }

    return receipt;
  }

  int GetFullPrice() const {
    return CreateReceipt().GetTotalPrice();
  }
};
