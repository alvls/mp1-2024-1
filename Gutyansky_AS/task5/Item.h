#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include "Barcode.h"

class Item {
private:
  Barcode m_Barcode;
  std::string m_Name;
  int m_Price;
  int m_Discount;

public:
  Item(const Barcode& barcode, const std::string& name, int price, int discount) : 
    m_Barcode(barcode), m_Name(name), m_Price(price), m_Discount(discount) {
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

  const Barcode& GetBarcode() const {
    return m_Barcode;
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

  int GetDiscountRubles() const {
    return m_Price * m_Discount / 100;
  }

  int GetPriceWithDiscount() const {
    return m_Price - GetDiscountRubles();
  }

  bool operator==(const Item& other) const {
    return m_Barcode == other.m_Barcode;
  }
};

std::ostream& operator<<(std::ostream& os, const Item& item);