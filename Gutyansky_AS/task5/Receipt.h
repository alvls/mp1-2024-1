#pragma once
#include <vector>
#include <stdexcept>
#include "Item.h"

class Receipt {
private:
  std::vector<std::pair<Item, int>> m_Items;

public:
  void AddItems(Item item, int amount) {
    if (amount <= 0) {
      throw std::runtime_error("Amount must be greater than zero");
    }

    m_Items.push_back(std::make_pair(item, amount));
  }

  int GetTotalDiscount() const {
    int sum = 0;
    for (auto& r : m_Items) {
      sum += r.first.GetDiscountRubles() * r.second;
    }

    return sum;
  }

  int GetTotalPrice() const {
    int sum = 0;
    for (auto& r : m_Items) {
      sum += r.first.GetPriceWithDiscount() * r.second;
    }

    return sum;
  }

  friend std::ostream& operator<<(std::ostream& os, const Receipt& receipt);
};

std::ostream& operator<<(std::ostream& os, const Receipt& receipt);