#include <iostream>
#include <Windows.h>

#include "Warehouse.h"
#include "WarehouseFileLoader.h"
#include "CashRegister.h"

Barcode GetBarcode() {
  std::string str;
  std::cout << "��������: ";
  std::cin >> str;
  return Barcode(str);
}

void Scan(CashRegister& cashRegister) {
  Barcode barcode = GetBarcode();
  cashRegister.ScanItem(barcode);
  std::cout << "����� �������� � ���. *������*\a\n";
}

void GetData(CashRegister& cashRegister) {
  Barcode barcode = GetBarcode();
  std::cout << cashRegister.GetItemInfo(barcode);
  std::cout << "�������� � ���? (y/n) ";
  std::string ans;
  std::cin >> ans;
  if (ans[0] == 'y') {
    cashRegister.ScanItem(barcode);
    std::cout << "����� ��������\n";
  }
}

void PrintReceipt(CashRegister& cashRegister) {
  std::cout << cashRegister.CreateReceipt();
}

void PrintPrice(CashRegister& cashRegister) {
  std::cout << "�������� ���������: " << cashRegister.GetFullPrice() << "��� \n";
}

void DeleteProduct(CashRegister& cashRegister) {
  Barcode barcode = GetBarcode();
  if (cashRegister.RemoveItem(barcode)) {
    std::cout << "�������� ���������.\n";
  }
  else {
    std::cout << "����� �� ������.\n";
  }
}

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  Warehouse* warehouse = LoadWarehouseFromFile("database.dat");
  CashRegister cashRegister(warehouse);

  while (true) {
    std::cout << "��������:\n"
      << "1. �������������\n"
      << "2. ������ ����������\n"
      << "3. ���\n"
      << "4. ���������� ���������\n"
      << "5. ������� ����� �� �������\n"
      << "6. �����\n"
      << "\n�����: ";

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
      std::cout << "���������� ��� ���\n";
    }
  }

  delete warehouse;
  return 0;
}