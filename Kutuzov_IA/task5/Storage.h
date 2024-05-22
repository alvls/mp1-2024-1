#pragma once

#include <string>
#include <map>

struct TItemData
{
	std::string Name = "NullItem";
	int Cost = 0;
	int Discount = 0;

	// Returs items cost with discount applied
	int GetActualCost();
};


class CStorage
{
	// Main data storage
	std::map<std::string, TItemData> ItemList;

public:
	// Default constructor
	CStorage(std::string DataBaseFileName = "ItemList.txt");

	// Finds item data in the list
	bool GetItemData(TItemData& OutItemData, std::string Code);

	// Checks if Code is valid
	bool IsValidCode(std::string& Code);

	// Reads data base from file
	void LoadDataBase(std::string FileName);

	
	// JUST FOR FUN: gets a random item from the List
	std::string GetRandomItemCode();
};