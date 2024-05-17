#pragma once
#include "Warehouse.h"
#include "Barcode.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

std::vector<std::string> split(const std::string& s, char delim = ',') {
  std::vector<std::string> elems;

  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

Warehouse* LoadWarehouseFromFile(const std::string& path) {
  std::ifstream is(path);
  
  Warehouse* warehouse = new Warehouse();
  size_t n;
  is >> n;
  std::string tmp;
  std::getline(is, tmp); // skip \n
  for (size_t i = 0; i < n; i++) {
    std::getline(is, tmp);
    std::vector<std::string> parsed = split(tmp, ';');
    Barcode barcode(parsed[0]);
    std::string name = parsed[1];
    int price = std::stoi(parsed[2]);
    int discount = std::stoi(parsed[3]);
    warehouse->RegisterItem(Item(barcode, name, price, discount));
  }

  return warehouse;
}