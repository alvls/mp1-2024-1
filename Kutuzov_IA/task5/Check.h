#pragma once
#include "Storage.h"

class CCheck
{
	// Main data: Code -> Item Count
	std::map<std::string, int> Items;

	int TotalCost;
	int TotalDiscount;
	int ToPay;


	CStorage* Storage;


public:
	// Constructor
	CCheck(CStorage* InStorage);

	// Adds an item to check
	bool AddItem(std::string& Code);

	// Removes an item to check
	bool RemoveItem(std::string& Code);

	// Returns total cost of all items in the check
	int GetTotalCost();

	// Returns total discount of all items in the check
	int GetTotalDiscount();

	// Returns the ammount of money the customer has to pay 
	int GetToPay();

	// Returns the number of different items in the check
	int GetItemCount();


	// Prints the check into the console
	void Print();
};