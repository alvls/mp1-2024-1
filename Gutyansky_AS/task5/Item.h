#pragma once
#include <string>
#include <stdexcept>

class Item {
private:
  std::string m_Name;
  int m_Price;
  int m_Discount;

public:
  Item(const std::string& name, int price, int discount) : m_Name(name), m_Price(price), m_Discount(discount) {
    if (name.empty()) {
      throw std::runtime_error("Name must be non empty");
    }

    if (price <= 0) {
      throw std::runtime_error("Price must be greater than zero");
    }

    if (discount < 1 || discount > 50) {
      throw std::runtime_error("Discount must be in [1;50]");
    }
  }

  const std::string& GetName() const {
    return m_Name;
  }

  int GetPrice() const {
    return m_Price;
  }

  int GetDiscount() const {
    return m_Discount;
  }
};
