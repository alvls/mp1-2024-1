#pragma once
#include "Warehouse.h"

// TODO: write this class
class Receipt;

class CashRegister {
private:
  Warehouse* m_Warehouse;

public:
  CashRegister(Warehouse* warehouse) : m_Warehouse(warehouse) {
    if (warehouse == nullptr) {
      throw std::runtime_error("No warehouse provided");
    }
  }

  void ScanItem(const std::string& code) {
    // Всё еще не понимаю чем отличается сканирование товара от добавления...
    AddItem(code);
  }

  void AddItem(const std::string& code) {

  }

  void RemoveItem(const std::string& code) {
    
  }

  Receipt CreateReceipt() const {

  }

  int GetFullPrice() const {

  }
};
