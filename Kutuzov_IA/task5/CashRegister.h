#pragma once
#include "Storage.h"
#include "Check.h"


class CCashRegister
{
	// Storage pointer
	CStorage* Storage;

	// The check of the current customer
	CCheck* CurrentCheck;

public:
	// Constructor
	CCashRegister(CStorage* InStorage);

	// Destructor
	~CCashRegister();

	// Scannes item and adds it to the check, returns "true" if successful
	bool ScanItem(std::string& Code);

	// Remove item from the check, returns "true" if successful
	bool RemoveItem(std::string& Code);

	// Finishes the current check and prints it out, also resetting the CashRegister for the next cusomer
	bool PrintOutCheck();

	// Prints scanned item data to the console (for the cashier)
	void PrintCashierInfo(std::string OperationName, std::string& Code);
};

