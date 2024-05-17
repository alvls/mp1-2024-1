#include <iostream>
#include <Windows.h>

#include "Warehouse.h"
#include "WarehouseFileLoader.h"
#include "CashRegister.h"

Barcode GetBarcode() {
  std::string str;
  std::cout << "Штрихкод: ";
  std::cin >> str;
  return Barcode(str);
}

void Scan(CashRegister& cashRegister) {
  Barcode barcode = GetBarcode();
  cashRegister.ScanItem(barcode);
  std::cout << "Товар добавлен в чек. *пиииип*\a\n";
}

void GetData(CashRegister& cashRegister) {
  Barcode barcode = GetBarcode();
  std::cout << cashRegister.GetItemInfo(barcode);
  std::cout << "Добавить в чек? (y/n) ";
  std::string ans;
  std::cin >> ans;
  if (ans[0] == 'y') {
    cashRegister.ScanItem(barcode);
    std::cout << "Товар добавлен\n";
  }
}

void PrintReceipt(CashRegister& cashRegister) {
  std::cout << cashRegister.CreateReceipt();
}

void PrintPrice(CashRegister& cashRegister) {
  std::cout << "Итоговая стоимость: " << cashRegister.GetFullPrice() << "руб \n";
}

void DeleteProduct(CashRegister& cashRegister) {
  Barcode barcode = GetBarcode();
  if (cashRegister.RemoveItem(barcode)) {
    std::cout << "Операция выполнена.\n";
  }
  else {
    std::cout << "Товар не найден.\n";
  }
}

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  Warehouse* warehouse = LoadWarehouseFromFile("database.dat");
  CashRegister cashRegister(warehouse);

  while (true) {
    std::cout << "Действие:\n"
      << "1. Отсканировать\n"
      << "2. Узнать информацию\n"
      << "3. Чек\n"
      << "4. Посмотреть стоимость\n"
      << "5. Удалить товар из покупки\n"
      << "6. Выход\n"
      << "\nВыбор: ";

    int choice;
    std::cin >> choice;
    if (choice == 6) {
      break;
    }

    try {
      switch (choice)
      {
      case 1: Scan(cashRegister); break;
      case 2: GetData(cashRegister); break;
      case 3: PrintReceipt(cashRegister); break;
      case 4: PrintPrice(cashRegister); break;
      case 5: DeleteProduct(cashRegister); break;
      }
    }
    catch (std::runtime_error& e) {
      std::cout << "Попробуйте ещё раз\n";
    }
  }

  delete warehouse;
  return 0;
}